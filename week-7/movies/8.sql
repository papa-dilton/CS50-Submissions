SELECT people.name
FROM people, stars, movies
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND movies.title LIKE "Toy Story"
;