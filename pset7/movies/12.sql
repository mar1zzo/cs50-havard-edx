SELECT movies.title FROM movies 
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Helena Bonham Carter"
INTERSECT
SELECT movies.title FROM movies 
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Johnny Depp";
