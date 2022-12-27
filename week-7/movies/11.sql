SELECT movies.title
FROM people, movies, ratings, stars
WHERE people.name LIKE "Chadwick Boseman"
AND people.id = stars.person_id
AND stars.movie_id = movies.id
AND movies.id = ratings.movie_id
ORDER BY ratings.rating DESC
LIMIT 5
;