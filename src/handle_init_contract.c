#include "morpho_plugin.h"

// Called once to init.
void handle_init_contract(ethPluginInitContract_t *msg) {
    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Print size of plugin's context.
    PRINTF("context size: %d / %d\n", sizeof(context_t), msg->pluginContextLength);

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    explicit_bzero(context, sizeof(*context));

    // Find tx selector
    size_t index;
    if (!find_selector(U4BE(msg->selector, 0), MORPHO_SELECTORS, NUM_SELECTORS, &index)) {
        PRINTF("can't find selector\n");
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }
    context->selectorIndex = index;

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case COMPOUND_SUPPLY:
        case COMPOUND_REPAY:
        case AAVE_SUPPLY:
        case AAVE_REPAY:
            context->next_param = _POOL_TOKEN_ADDRESS_SUPPLY_REPAY;
            break;
        case COMPOUND_WITHDRAW:
        case COMPOUND_BORROW:
        case AAVE_WITHDRAW:
        case AAVE_BORROW:
            context->next_param = _POOL_TOKEN_ADDRESS_WITHDRAW_BORROW;
            break;
        case COMPOUND_CLAIM_REWARDS:
        case AAVE_CLAIM_REWARDS:
            context->next_param = OFFSET_C_TOKEN_ADDRESSES;
            break;
        case COMMON_CLAIM:
            context->next_param = _ACCOUNT;
            break;
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
