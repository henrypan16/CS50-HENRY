SELECT COUNT(movies.title) FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating = '10.0'