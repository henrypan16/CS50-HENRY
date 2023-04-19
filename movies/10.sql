SELECT people.name FROM movies
INNER JOIN directors ON movies.id = directors.movie_id
INNER JOIN people ON directors.person_id = people.id
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >= '9.0'