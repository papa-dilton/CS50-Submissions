SELECT AVG( rating )
FROM ratings, movies
WHERE movie_id = id
AND year = 2012
;