SELECT movies.title FROM movies
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON stars.person_id = people.id
WHERE people.name = 'Johnny Depp' OR people.name = 'Helena Bonham Carter'
GROUP BY movies.id
HAVING COUNT(*)>1