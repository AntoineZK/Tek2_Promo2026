{-
-- EPITECH PROJECT, 2023
-- B-FUN-400-NCY-4-1-wolfram-antoine.khalidy
-- File description:
-- Lib
-}

module Lib
    ( allRules
    ) where

import Data.Bits ( Bits((.&.), shiftR) )

allRules :: Int -> Char -> Char -> Char -> Char
allRules rule '*' '*' '*' = if (rule `shiftR` 7) .&. 1 == 1 then '*' else ' '
allRules rule '*' '*' ' ' = if (rule `shiftR` 6) .&. 1 == 1 then '*' else ' '
allRules rule '*' ' ' '*' = if (rule `shiftR` 5) .&. 1 == 1 then '*' else ' '
allRules rule '*' ' ' ' ' = if (rule `shiftR` 4) .&. 1 == 1 then '*' else ' '
allRules rule ' ' '*' '*' = if (rule `shiftR` 3) .&. 1 == 1 then '*' else ' '
allRules rule ' ' '*' ' ' = if (rule `shiftR` 2) .&. 1 == 1 then '*' else ' '
allRules rule ' ' ' ' '*' = if (rule `shiftR` 1) .&. 1 == 1 then '*' else ' '
allRules rule ' ' ' ' ' ' = if rule .&. 1 == 1 then '*' else ' '
allRules _ _ _ _ = ' '

