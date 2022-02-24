--primeHelper :: Integer-> Integer -> Integer
primeHelper n div
    | n < 2 = False
    | div == n = True
    | n `mod` div == 0 = False
    | otherwise = primeHelper n (div + 1)
 
--prime :: Integer -> Bool
prime n = primeHelper n 2

primesDecomp n = head [(a, b) | a <- [1..n], b <- [1..n], prime a,prime b, a + b == n]