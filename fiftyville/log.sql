-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find the crime report desciption => Found out the time of theft (10:15AM)
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = 'Humphrey Street'

--Find the interview on July 28 Ruth that include the word thief
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28
	AND transcript LIKE '%thief%'

--Ruth testimony let us know that within 10 minutes of the theft, the thief exit the bakery
--Find the name of the people exiting the bakery between 10:15AM and 10:25AM
SELECT people.name
FROM bakery_security_logs
	INNER JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.month = 7
	AND bakery_security_logs.day = 28
	AND bakery_security_logs.activity = 'exit'
	AND bakery_security_logs.hour = 10
	AND bakery_security_logs.minute >= 15
	AND bakery_security_logs.minute <= 25

--Eugene testimony let us know that the thief withraw money from an atm on Leggett Street earlier that day
--Find the name of the people withdraw money on Leggett Street on July 28
SELECT people.name
FROM people
	INNER JOIN bank_accounts ON people.id = bank_accounts.person_id
	INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.atm_location = 'Leggett Street'
	AND atm_transactions.month = 7
	AND atm_transactions.day = 28
	AND atm_transactions.transaction_type = 'withdraw'

--Raymond testimony let us know that the thief call someone for less than a minute, and have a earliest flight ticket out of Fiftyville tomorrow (July 29)
--Find the name of the caller on July 28 with call duration shorter than 1 minute
SELECT people.name
FROM people
	INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.month = 7
	AND phone_calls.day = 28
	AND phone_calls.duration < 60

--Find the name of people that have the earliest flight ticket on July 29 from Fiftyville
SELECT people.name
FROM flights
	INNER JOIN passengers ON flights.id = passengers.flight_id
	INNER JOIN people ON passengers.passport_number = people.passport_number
	INNER JOIN airports ON airports.id = flights.origin_airport_id
WHERE flights.day = 29
	AND flights.month = 7
	AND airports.city = 'Fiftyville'
	AND flights.hour IN (
		SELECT MIN(hour) FROM flights
		WHERE day = 29 AND month = 7)

--Find the name of the person that appear in all 4 queries
SELECT people.name
FROM people
WHERE people.name IN
	(
		SELECT people.name
		FROM bakery_security_logs
			INNER JOIN people ON bakery_security_logs.license_plate = people.license_plate
		WHERE bakery_security_logs.month = 7
			AND bakery_security_logs.day = 28
			AND bakery_security_logs.activity = 'exit'
			AND bakery_security_logs.hour = 10
			AND bakery_security_logs.minute >= 15
			AND bakery_security_logs.minute <= 25
	)
	AND people.name IN
	(
		SELECT people.name
		FROM people
			INNER JOIN bank_accounts ON people.id = bank_accounts.person_id
			INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
		WHERE atm_transactions.atm_location = 'Leggett Street'
			AND atm_transactions.month = 7
			AND atm_transactions.day = 28
			AND atm_transactions.transaction_type = 'withdraw'
	)
	AND people.name IN
	(
		SELECT people.name
		FROM people
			INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
		WHERE phone_calls.month = 7
			AND phone_calls.day = 28
			AND phone_calls.duration < 60
	)
	AND people.name IN
	(
		SELECT people.name
		FROM flights
			INNER JOIN passengers ON flights.id = passengers.flight_id
			INNER JOIN people ON passengers.passport_number = people.passport_number
			INNER JOIN airports ON airports.id = flights.origin_airport_id
		WHERE flights.day = 29
			AND flights.month = 7
			AND airports.city = 'Fiftyville'
			AND flights.hour IN (
				SELECT MIN(hour) FROM flights
				WHERE day = 29 AND month = 7)
	)

--Find the name of the accomplice
SELECT name
FROM people
WHERE phone_number IN (
	SELECT phone_calls.receiver
	FROM people
		INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
	WHERE people.name = 'Bruce'
		AND phone_calls.month = 7
		AND phone_calls.day = 28
		AND phone_calls.duration < 60
	)

--Find the destination city
SELECT airports.city
FROM airports
	INNER JOIN flights ON airports.id = flights.destination_airport_id
	INNER JOIN passengers ON flights.id = passengers.flight_id
	INNER JOIN people ON passengers.passport_number = people.passport_number
WHERE people.name = 'Bruce'