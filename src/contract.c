/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdint.h>
#include "morpho_plugin.h"

// List of selectors supported by this plugin.
static const uint32_t COMPOUND_SUPPLY_SELECTOR = 0x0c0a769b;
static const uint32_t COMPOUND_REPAY_SELECTOR = 0x1da649cf;
static const uint32_t COMPOUND_WITHDRAW_SELECTOR = 0xf3fef3a3;
static const uint32_t COMPOUND_BORROW_SELECTOR = 0x4b8a3529;
static const uint32_t COMPOUND_CLAIM_REWARDS_SELECTOR = 0x148e23ce;

static const uint32_t AAVE_SUPPLY_SELECTOR = 0x0c0a769b;
static const uint32_t AAVE_REPAY_SELECTOR = 0x1da649cf;
static const uint32_t AAVE_WITHDRAW_SELECTOR = 0xf3fef3a3;
static const uint32_t AAVE_BORROW_SELECTOR = 0x4b8a3529;
static const uint32_t AAVE_CLAIM_REWARDS_SELECTOR = 0x3111e7b3;

static const uint32_t COMMON_CLAIM_SELECTOR = 0x3d13f874;

// Array of all the different Morpho.sol and RewardsDistributors.sol selectors. (Compound / Aave and
// Common)
const uint32_t MORPHO_SELECTORS[NUM_SELECTORS] = {
    COMPOUND_SUPPLY_SELECTOR,
    COMPOUND_REPAY_SELECTOR,
    COMPOUND_WITHDRAW_SELECTOR,
    COMPOUND_BORROW_SELECTOR,
    COMPOUND_CLAIM_REWARDS_SELECTOR,
    AAVE_SUPPLY_SELECTOR,
    AAVE_REPAY_SELECTOR,
    AAVE_WITHDRAW_SELECTOR,
    AAVE_BORROW_SELECTOR,
    AAVE_CLAIM_REWARDS_SELECTOR,
    COMMON_CLAIM_SELECTOR,
};
