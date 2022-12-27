SELECT DISTINCT people.name
FROM people, stars, movies, people Bacon, stars BaconStars
WHERE Bacon.name = "Kevin Bacon"
AND Bacon.birth = 1958
AND BaconStars.person_id = Bacon.id
AND BaconStars.movie_id = movies.id
AND stars.movie_id = movies.id
AND stars.person_id = people.id
AND people.id <> Bacon.id
ORDER BY people.name
;