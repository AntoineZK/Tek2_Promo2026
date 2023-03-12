{-
-- EPITECH PROJECT, 2023
-- B-FUN-400-NCY-4-1-wolfram-antoine.khalidy
-- File description:
-- Main
-}

module Main (main) where

import Lib (allRules)
import System.Environment ( getArgs )
import System.Exit ( exitWith, ExitCode(ExitFailure) )

data Conf = Conf {
    rule :: Int,
    start :: Int,
    line :: Maybe Int,
    window :: Int,
    move :: Int
}

getOpts :: Conf -> [String] -> Maybe Conf
getOpts conf (x:y:xs) = case x of
    "--rule" -> getOpts conf {rule = read y} xs
    "--start" -> getOpts conf {start = read y} xs
    "--lines" -> getOpts conf {line = Just (read y)} xs
    "--window" -> getOpts conf {window = read y} xs
    "--move" -> getOpts conf {move = read y} xs
    _ -> Nothing
getOpts conf [] = Just conf
getOpts _ _ = Nothing

generateLine :: Int -> String -> String
generateLine ruleVal (a:b:c:xs) =
    allRules ruleVal a b c : generateLine ruleVal (b:c:xs)
generateLine _ _ = []

addSpace :: Int -> Int -> String -> String
addSpace nbMove nbWindow oldLine =
    let nbSpace = nbWindow - length oldLine
        nbSpaceLeft = nbSpace `div` 2
        nbSpaceRight = nbSpace `div` 2
    in replicate (nbSpaceLeft + 1) ' ' ++ oldLine ++ replicate nbSpaceRight ' '

removeCharacter :: Int -> Int -> String -> String
removeCharacter nbMove nbWindow oldLine =
    let nbRemove = length oldLine `div` 2 - nbWindow `div` 2
        removeBegin = drop nbRemove oldLine
    in take nbWindow removeBegin

formatLine :: Int -> Int -> String -> String
formatLine nbMove nbWindow oldLine =
    if length oldLine < nbWindow then
        addSpace nbMove nbWindow oldLine
    else
        removeCharacter nbMove nbWindow oldLine

getNbLine :: Conf -> Int
getNbLine conf = case line conf of
    Just nb -> nb
    Nothing -> -1

infiniteOrNot :: Int -> String -> Int -> Conf -> IO ()
infiniteOrNot nbLine newLine startVal conf =
    if nbLine == -1 then
        loop conf newLine (-1) (startVal + 1)
    else
        loop conf newLine (nbLine - 1) (startVal + 1)

loop :: Conf -> String -> Int -> Int -> IO ()
loop _ _ 0 _ = return ()
loop conf oldLine nbLine startVal =
    let newLine = generateLine (rule conf) ("  " ++ oldLine ++ "  ")
        formatedLine = formatLine (move conf) (window conf) oldLine
    in
        if startVal >= start conf then
            putStrLn formatedLine >> infiniteOrNot nbLine newLine startVal conf
        else
            loop conf newLine nbLine (startVal + 1)

checkNbArgs :: [String] -> IO ()
checkNbArgs args =
    if length args < 2 then
        putStrLn "Invalid arguments" >> exitWith (ExitFailure 84)
    else
        return ()

main :: IO ()
main = do
    args <- getArgs
    checkNbArgs args
    let maybeConf = getOpts (Conf 0 0 Nothing 80 0) args
    case maybeConf of
        Just conf -> if rule conf > 0 && rule conf <= 256 then
                loop conf "*" (getNbLine conf) 0
            else
                putStrLn "Invalid arguments" >> exitWith (ExitFailure 84)
        Nothing -> putStrLn "Invalid arguments" >> exitWith (ExitFailure 84)
