#include "morpho_plugin.h"
#include "text.h"

const uint8_t COMPOUND_MORPHO[ADDRESS_LENGTH] = {0x88, 0x88, 0x88, 0x2F, 0x8F, 0x84, 0x38,
                                                 0x96, 0x69, 0x98, 0x69, 0x17, 0x9F, 0xB6,
                                                 0xE4, 0xF7, 0xE3, 0xB5, 0x88, 0x88};
const uint8_t AAVE_MORPHO[ADDRESS_LENGTH] = {0x77, 0x77, 0x77, 0xc9, 0x89, 0x8D, 0x38,
                                             0x4F, 0x78, 0x5E, 0xe4, 0x4A, 0xcf, 0xe9,
                                             0x45, 0xef, 0xDF, 0xf5, 0xf3, 0xE0};
const uint8_t COMMON_REWARDS_DISTRIBUTOR[ADDRESS_LENGTH] = {
    0x3b, 0x14, 0xe5, 0xc7, 0x3e, 0x0a, 0x56, 0xd6, 0x07, 0xa8,
    0x68, 0x80, 0x98, 0x32, 0x6f, 0xd4, 0xb4, 0x29, 0x21, 0x35};

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    if (!(memcmp(COMPOUND_MORPHO, msg->pluginSharedRO->txContent->destination, ADDRESS_LENGTH)))
        strlcpy(msg->version, MSG_COMPOUND_ID, msg->versionLength);
    else if (!(memcmp(AAVE_MORPHO, msg->pluginSharedRO->txContent->destination, ADDRESS_LENGTH)))
        strlcpy(msg->version, MSG_AAVE_ID, msg->versionLength);
    else if (!(memcmp(COMMON_REWARDS_DISTRIBUTOR,
                      msg->pluginSharedRO->txContent->destination,
                      ADDRESS_LENGTH)))
        strlcpy(msg->version, MSG_REWARDS_DISTRIBUTOR_ID, msg->versionLength);
    else {
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
