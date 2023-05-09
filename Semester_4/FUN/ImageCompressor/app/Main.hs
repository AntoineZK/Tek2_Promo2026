{-
-- EPITECH PROJECT, 2023
-- B-FUN-400-NCY-4-1-compressor-yoan.gerard
-- File description:
-- Main
-}

import System.Random
import System.Environment
import System.Exit
import Lib
import Data.List (nub)

data Argv = Argv {
    nbClu :: Int,
    conLim :: Float,
    pathFile :: String
}

data Pixel = Pixel {
    point :: (Int, Int),
    color :: (Int, Int, Int)
} deriving (Show)

data Cluster = Cluster {
    center :: (Int, Int, Int),
    pixel :: [Pixel],
    ide :: Int
} deriving (Show)

getsmal :: (Int, Int, Int) -> Cluster -> Cluster -> Cluster
getsmal (r, g, b) (Cluster (x, y, z) xs i) (Cluster (a, d, c) ys l) =
    if (getDistance (r, g, b) (x, y, z) < getDistance (r, g, b) (a, d, c))
    then (Cluster (x, y, z) xs i) else (Cluster (a, d, c) ys l)

getsmallerDistance :: Pixel -> [Cluster] -> Cluster
getsmallerDistance _ [] = Cluster (999, 999, 999) [] 0
getsmallerDistance (Pixel (x, y) (r, g, b)) (z:zs) =
    getsmal (r, g, b) z (getsmallerDistance (Pixel (x, y) (r, g, b)) zs)

checkID :: Cluster -> Cluster -> Bool
checkID (Cluster _ _ i) (Cluster _ _ l) =
    if (i == l) then True else False

addpicluster :: Pixel -> Cluster -> Cluster
addpicluster (Pixel (x, y) (r, g, b)) (Cluster (a, d, c) ys l) =
    Cluster (a, d, c) (ys ++ [Pixel (x, y) (r, g, b)]) l

putPixelInCluster :: Pixel -> [Cluster] -> Cluster -> [Cluster]
putPixelInCluster _ [] _ = []
putPixelInCluster pix (z:zs) cl =
    if (checkID z cl) then [addpicluster pix z] ++ putPixelInCluster pix zs cl
    else [z] ++ putPixelInCluster pix zs cl

addPixelToCluster :: Pixel -> [Cluster] -> [Cluster]
addPixelToCluster _ [] = []
addPixelToCluster pix cl =
    putPixelInCluster pix cl (getsmallerDistance pix cl)

sortPixels :: [Pixel] -> [Cluster] -> [Cluster]
sortPixels [] clusters = clusters
sortPixels (x:xs) clusters = sortPixels xs (addPixelToCluster x clusters)

addrgb :: (Int, Int, Int) -> (Int, Int, Int) -> (Int, Int, Int)
addrgb (r1, g1, b1) (r2, g2, b2) = (r1 + r2, g1 + g2, b1 + b2)

addpixel :: [Pixel] -> (Int, Int, Int)
addpixel [] = (0, 0, 0)
addpixel (x:xs) = addrgb (color x) (addpixel xs)

countpixel :: [Pixel] -> Int
countpixel [] = 0
countpixel (_:xs) = 1 + countpixel xs

divrgb :: (Int, Int, Int) -> Int -> (Int, Int, Int)
divrgb (r, g, b) n = (div r n, div g n, div b n)

computeCenter :: Cluster -> (Int, Int, Int)
computeCenter (Cluster (x, y, z) [] _) = (x, y, z)
computeCenter (Cluster _ xs _) = divrgb (addpixel xs) (countpixel xs)

checkconvergence :: [Cluster] -> Float -> Bool
checkconvergence [] _ = True
checkconvergence ((Cluster (x, y, z) xs i):ys) n =
    if (getDistance (x, y, z) (computeCenter (Cluster (x, y, z) xs i)) > n)
    then False else checkconvergence ys n

centerList :: [Cluster] -> [Cluster]
centerList [] = []
centerList ((Cluster rgb xs i):ys) =
    [Cluster (computeCenter (Cluster rgb xs i)) xs i] ++ centerList ys

getOpts :: Argv -> [String] -> Maybe Argv
getOpts argv (x:y:xs) = case x of
    "-n" -> getOpts argv {nbClu = read y} xs
    "-l" -> getOpts argv {conLim = read y} xs
    "-f" -> getOpts argv {pathFile = y} xs
    _ -> Nothing
getOpts argv [] = Just argv
getOpts _ _ = Nothing

toPixel :: [(Int, Int)] -> [(Int, Int, Int)] -> [Pixel]
toPixel [] _ = []
toPixel _ [] = []
toPixel (x:xs) (y:ys) = Pixel x y : toPixel xs ys

getPixels :: String -> [Pixel]
getPixels str = toPixel xyPairs uniqueRgbTuples
    where
        wordsOfFile = map words (lines str)
        xyPairs = map readTuple (map head (wordsOfFile))
        rgbTuples = map readTruple (map last wordsOfFile)
        uniqueRgbTuples = nub rgbTuples

agnToClu :: Int -> [Pixel] -> Int -> Cluster
agnToClu i pix x = Cluster { center = color (pix !! i), pixel = [], ide = x }

isUniqueInt :: [Int] -> Int -> Bool
isUniqueInt [] _ = True
isUniqueInt (x:xs) newInt =
    if newInt == x
    then False
    else isUniqueInt xs newInt

getListIndex :: Int -> Int -> StdGen -> [Int] -> [Int]
getListIndex 0 _ _ act = act
getListIndex nb len seed act =
    let (newInt, newSeed) = randomR (0, len) seed :: (Int, StdGen)
        isUnique = isUniqueInt act newInt
    in
        if isUnique
            then getListIndex (nb - 1) len newSeed (newInt : act)
            else getListIndex nb len newSeed act

genAllClu :: Int -> [Int] -> [Pixel] -> [Cluster]
genAllClu _ [] _ = []
genAllClu i (x:xs) pix = agnToClu x pix i : genAllClu (i + 1) xs pix

nCl :: [Cluster] -> [Cluster]
nCl [] = []
nCl ((Cluster rgb _ i):ys) =
    [Cluster rgb [] i] ++ nCl ys

compressor :: [Cluster] -> [Pixel] -> Float -> [Cluster]
compressor clusters [] _ = clusters
compressor clusters pixs limit = if checkconvergence clusters limit
    then centerList clusters
    else compressor (sortPixels pixs (nCl (centerList clusters))) pixs limit

printPixels :: [Pixel] -> IO ()
printPixels [] = return ()
printPixels ((Pixel (x, y) (r, g, b)):xs) =
    putStr ("(" ++ show x ++ "," ++ show y ++ ") ") >>
    putStrLn ("(" ++ show r ++ "," ++ show g ++ "," ++ show b ++ ")") >>
    printPixels xs

prClusters :: [Cluster] -> IO ()
prClusters [] = return ()
prClusters ((Cluster (r, g, b) pixels _):xs) =
    putStrLn "--" >>
    putStrLn ("(" ++ show r ++ "," ++ show g ++ "," ++ show b ++ ")") >>
    putStrLn "-" >>
    printPixels pixels >>
    prClusters xs

main :: IO ()
main = do
    args <- getArgs
    if (length args) < 6
        then putStrLn "Invalid arguments" >> exitWith (ExitFailure 84)
        else return ()
    seed <- newStdGen
    procCompressor seed args

procCompressor :: StdGen -> [String] -> IO ()
procCompressor seed args =
    case getOpts (Argv 0 0 "") args of
        Just argv -> do
            contents <- readFile (pathFile argv)
            let pixels = getPixels contents
            prResult seed argv pixels
        _ -> putStrLn "Invalid arguments" >> exitWith (ExitFailure 84)

prResult :: StdGen -> Argv -> [Pixel] -> IO ()
prResult seed argv pixels =
    let nb = if nbClu argv > length pixels
            then length pixels
            else nbClu argv
        list = getListIndex nb (length pixels - 1) seed []
        aC = genAllClu 0 list pixels
    in prClusters (compressor (sortPixels pixels aC) pixels (conLim argv))
