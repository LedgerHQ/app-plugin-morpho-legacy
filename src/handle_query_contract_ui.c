#include <stdbool.h>
#include "morpho_plugin.h"
#include "text.h"

static bool handle_warning_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    if (context->token_warning && msg->screenIndex == 1) {
        strlcpy(msg->title, TITLE_WARNING_UI, msg->titleLength);
        strlcpy(msg->msg, MSG_TOKEN_WARNING_UI, msg->msgLength);
        ret = true;
    } else if (context->on_behalf) {
        strlcpy(msg->title, TITLE_ON_BEHALF_UI, msg->titleLength);
        msg->msg[0] = '0';
        msg->msg[1] = 'x';
        ret = getEthAddressStringFromBinary((uint8_t *) context->user_address,
                                            msg->msg + 2,
                                            msg->pluginSharedRW->sha3,
                                            0);
    } else {
        PRINTF("ERROR IN HANDLE WARNING UI\n");
    }
    return ret;
}

static bool handle_supply_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        // Edit these cases to change screens.
        case 0:
            strlcpy(msg->title, TITLE_SUPPLY_UI, msg->titleLength);
            // displays ticker and amount.
            ret = amountToString(context->amount,
                                 sizeof(context->amount),
                                 context->token_decimals,
                                 context->token_ticker,
                                 msg->msg,
                                 msg->msgLength);
            break;
        case 1:
        case 2:
            ret = handle_warning_ui(msg, context);
            break;
        default:
            PRINTF("ERROR IN HANDLE SUPPLY UI\n");
            break;
    }
    return ret;
}

static bool handle_repay_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, TITLE_REPAY_UI, msg->titleLength);
            ret = amountToString(context->amount,
                                 sizeof(context->amount),
                                 context->token_decimals,
                                 context->token_ticker,
                                 msg->msg,
                                 msg->msgLength);
            break;
        case 1:
        case 2:
            ret = handle_warning_ui(msg, context);
            break;
        default:
            PRINTF("ERROR IN HANDLE REPAY UI\n");
            break;
    }
    return ret;
}

static bool handle_withdraw_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, TITLE_WITHDRAW_UI, msg->titleLength);
            ret = amountToString(context->amount,
                                 sizeof(context->amount),
                                 context->token_decimals,
                                 context->token_ticker,
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("ERROR IN HANDLE WITHDRAW UI\n");
            break;
    }
    return ret;
}

static bool handle_borrow_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, TITLE_BORROW_UI, msg->titleLength);
            ret = amountToString(context->amount,
                                 sizeof(context->amount),
                                 context->token_decimals,
                                 context->token_ticker,
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("ERROR IN HANDLE BORROW UI\n");
            break;
    }
    return ret;
}

static bool handle_claim_rewards_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, TITLE_CLAIM_REWARDS_UI, msg->titleLength);
            if (context->trade_for_morpho)
                strlcpy(msg->msg, MSG_CLAIM_REWARDS_MORPHO_UI, msg->msgLength);
            else
                strlcpy(msg->msg, MSG_CLAIM_REWARDS_OTHERS_UI, msg->msgLength);
            ret = true;
            break;
        default:
            PRINTF("ERROR IN HANDLE CLAIM REWARDS UI\n");
            break;
    }
    return ret;
}
static bool handle_claim_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, TITLE_CLAIM_REWARDS_UI, msg->titleLength);
            strlcpy(msg->msg, MSG_CLAIM_UI, msg->msgLength);
            ret = true;
            break;
        case 1:
            ret = handle_warning_ui(msg, context);
            break;
        default:
            PRINTF("ERROR IN HANDLE CLAIM UI\n");
            break;
    }
    return ret;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // Clean the display fields.
    explicit_bzero(msg->title, msg->titleLength);
    explicit_bzero(msg->msg, msg->msgLength);

    switch (context->selectorIndex) {
        case COMPOUND_SUPPLY:
        case AAVE_SUPPLY:
            ret = handle_supply_ui(msg, context);
            break;
        case COMPOUND_REPAY:
        case AAVE_REPAY:
            ret = handle_repay_ui(msg, context);
            break;
        case COMPOUND_WITHDRAW:
        case AAVE_WITHDRAW:
            ret = handle_withdraw_ui(msg, context);
            break;
        case COMPOUND_BORROW:
        case AAVE_BORROW:
            ret = handle_borrow_ui(msg, context);
            break;
        case COMPOUND_CLAIM_REWARDS:
        case AAVE_CLAIM_REWARDS:
            ret = handle_claim_rewards_ui(msg, context);
            break;
        case COMMON_CLAIM:
            ret = handle_claim_ui(msg, context);
            break;
        default:
            PRINTF("Error in handle_query_contract_ui's selectorIndex switch\n");
            break;
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
