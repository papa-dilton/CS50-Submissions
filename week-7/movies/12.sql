SELECT movies.title
FROM movies, stars S1, stars S2, people P1, people P2
WHERE P1.id <> P2.id
AND movies.id = S1.movie_id
AND movies.id = S2.movie_id
AND P1.id = S1.person_id
AND P2.id = S2.person_id
AND P1.name = "Johnny Depp"
AND P2.name = "Helena Bonham Carter"
;