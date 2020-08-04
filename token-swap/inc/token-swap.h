/* Autogenerated SPL Token-Swap program C Bindings */

#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * fee rate as a ratio
 */
typedef struct TokenSwap_Fee {
    /**
     * denominator of the fee ratio
     */
    uint64_t denominator;
    /**
     * numerator of the fee ratio
     */
    uint64_t numerator;
} TokenSwap_Fee;

/**
 * Instructions supported by the SwapInfo program.
 */
typedef enum TokenSwap_SwapInstruction_Tag {
    /**
     *   Initializes a new SwapInfo.
     *
     *   0. `[writable, signer]` New Token-swap to create.
     *   1. `[]` $authority derived from `create_program_address(&[Token-swap account])`
     *   2. `[]` token_a Account. Must be non zero, owned by $authority.
     *   3. `[]` token_b Account. Must be non zero, owned by $authority.
     *   4. `[writable]` pool Token. Must be empty, owned by $authority.
     *   5. `[writable]` Pool Account to deposit the generated tokens, user is the owner.
     *   6. '[]` Token program id
     *   userdata: fee rate as a ratio
     */
    Initialize,
    /**
     *   Swap the tokens in the pool.
     *
     *   0. `[]` Token-swap
     *   1. `[]` $authority
     *   2. `[writable]` token_(A|B) SOURCE Account, amount is transferable by $authority,
     *   4. `[writable]` token_(A|B) Base Account to swap INTO.  Must be the SOURCE token.
     *   5. `[writable]` token_(A|B) Base Account to swap FROM.  Must be the DEST token.
     *   6. `[writable]` token_(A|B) DEST Account assigned to USER as the owner.
     *   7. '[]` Token program id
     *   userdata: SOURCE amount to transfer, output to DEST is based on the exchange rate
     */
    Swap,
    /**
     *   Deposit some tokens into the pool.  The output is a "pool" token representing ownership
     *   into the pool. Inputs are converted to the current ratio.
     *
     *   0. `[]` Token-swap
     *   1. `[]` $authority
     *   2. `[writable]` token_a $authority can transfer amount,
     *   4. `[writable]` token_b $authority can transfer amount,
     *   6. `[writable]` token_a Base Account to deposit into.
     *   7. `[writable]` token_b Base Account to deposit into.
     *   8. `[writable]` Pool MINT account, $authority is the owner.
     *   9. `[writable]` Pool Account to deposit the generated tokens, user is the owner.
     *   10. '[]` Token program id
     *   userdata: token_a amount to transfer.  token_b amount is set by the current exchange rate.
     */
    Deposit,
    /**
     *   Withdraw the token from the pool at the current ratio.
     *
     *   0. `[]` Token-swap
     *   1. `[]` $authority
     *   2. `[writable]` SOURCE Pool account, amount is transferable by $authority.
     *   5. `[writable]` token_a Account to withdraw FROM.
     *   6. `[writable]` token_b Account to withdraw FROM.
     *   7. `[writable]` token_a user Account.
     *   8. `[writable]` token_b user Account.
     *   9. '[]` Token program id
     *   userdata: SOURCE amount of pool tokens to transfer. User receives an output based on the
     *   percentage of the pool tokens that are returned.
     */
    Withdraw,
} TokenSwap_SwapInstruction_Tag;

typedef struct TokenSwap_Initialize_Body {
    TokenSwap_Fee _0;
} TokenSwap_Initialize_Body;

typedef struct TokenSwap_Swap_Body {
    TokenSwap_U256 _0;
} TokenSwap_Swap_Body;

typedef struct TokenSwap_Deposit_Body {
    TokenSwap_U256 _0;
} TokenSwap_Deposit_Body;

typedef struct TokenSwap_Withdraw_Body {
    TokenSwap_U256 _0;
} TokenSwap_Withdraw_Body;

typedef struct TokenSwap_SwapInstruction {
    TokenSwap_SwapInstruction_Tag tag;
    union {
        TokenSwap_Initialize_Body initialize;
        TokenSwap_Swap_Body swap;
        TokenSwap_Deposit_Body deposit;
        TokenSwap_Withdraw_Body withdraw;
    };
} TokenSwap_SwapInstruction;

typedef uint8_t TokenSwap_Pubkey[32];

/**
 * Initialized program details.
 */
typedef struct TokenSwap_SwapInfo {
    /**
     * Token A
     * The Liquidity token is issued against this value.
     */
    TokenSwap_Pubkey token_a;
    /**
     * Token B
     */
    TokenSwap_Pubkey token_b;
    /**
     * Pool tokens are issued when A or B tokens are deposited.
     * Pool tokens can be withdrawn back to the original A or B token.
     */
    TokenSwap_Pubkey pool_mint;
    /**
     * Fee applied to the input token amount prior to output calculation.
     */
    TokenSwap_Fee fee;
} TokenSwap_SwapInfo;

/**
 * Program states.
 */
typedef enum TokenSwap_State_Tag {
    /**
     * Unallocated state, may be initialized into another state.
     */
    Unallocated,
    /**
     * Initialized state.
     */
    Init,
} TokenSwap_State_Tag;

typedef struct TokenSwap_Init_Body {
    TokenSwap_SwapInfo _0;
} TokenSwap_Init_Body;

typedef struct TokenSwap_State {
    TokenSwap_State_Tag tag;
    union {
        TokenSwap_Init_Body init;
    };
} TokenSwap_State;
