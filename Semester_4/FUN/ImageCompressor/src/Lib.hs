{-
-- EPITECH PROJECT, 2023
-- B-FUN-400-NCY-4-1-compressor-yoan.gerard
-- File description:
-- Lib
-}

module Lib
    ( readTuple, readTruple, getDistance ) where

readTuple :: String -> (Int, Int)
readTuple str = read str :: (Int, Int)

readTruple :: String -> (Int, Int, Int)
readTruple str = read str :: (Int, Int, Int)

getDistance :: (Int, Int, Int) -> (Int, Int, Int) -> Float
getDistance (r1, g1, b1) (r2, g2, b2) =
    sqrt (fromIntegral (r1 - r2) ^ (2 :: Int)
        + fromIntegral (g1 - g2) ^ (2 :: Int)
        + fromIntegral ((b1 - b2) ^ (2 :: Int)))
