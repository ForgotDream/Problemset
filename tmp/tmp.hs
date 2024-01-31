fact :: Integer -> Integer
fact 0 = 1
fact a = a * fact (a - 1)

comb :: Integer -> Integer -> Integer
comb a b = div (fact a) (fact b * fact (a - b))

main = interact $ show . product . map read . words
