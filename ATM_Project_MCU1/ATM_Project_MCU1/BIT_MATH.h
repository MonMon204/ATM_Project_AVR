/*
 * BIT_MATH.h
 *
 * Created: 1/28/2024 6:03:20 PM
 * Author: Mina Waguih
 * Description: Commonly used Macros
 *
 */ 

#ifndef BIT_MATH_H
#define BIT_MATH_H

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT)     (REG |= (1<<BIT))

/* Clear a certain bit in any register */
#define CLR_BIT(REG,BIT)     (REG &= (~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT)  (REG ^= (1<<BIT))

/* Get a certain bit in any register */
#define GET_BIT(REG,BIT)     (( REG & (1<<BIT)) >> BIT)

/* Creates a bit mask with only the specified bit set */
#define MASK(BIT)            (1 << BIT)

/* Checks if the specified bit in the register is set to 1 */
#define BIT_IS_SET(REG,BIT)  ((REG & MASK(BIT)) != 0)

/* Checks if the specified bit in the register is cleared to 0 */
#define BIT_IS_CLR(REG,BIT)  ((REG & MASK(BIT)) == 0)


#endif
