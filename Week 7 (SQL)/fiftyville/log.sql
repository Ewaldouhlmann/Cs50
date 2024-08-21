-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND street = 'Humphrey Street';


-- Getting the interviews info --
SELECT id,name, transcript
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28;

-- Getting the logs from bakery --
SELECT *
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2023
AND hour = 10
AND minute <= 25
AND minute >= 15
AND activity = 'exit';

-- getting info by phone calls --
SELECT *
FROM phone_calls
WHERE day = 28
AND month = 7
AND year = 2023
AND duration <= 60;

/*Getting people with calls duration smaller or equal to 1 minute, and left 10 minutes after the robbery*/
SELECT DISTINCT people.name, people.phone_number, people.license_plate
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE phone_calls.day = 28
AND phone_calls.month = 7
AND phone_calls.year = 2023
AND phone_calls.duration <= 60
AND phone_calls.caller = people.phone_number
AND people.license_plate IN
    (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND hour = 10
    AND minute <= 25
    AND minute >= 15
    AND activity = 'exit'
    );

/*Getting info by bank transactions*/
SELECT people.name
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.year = 2023;

/*Getting people who will travell in flyes tomorrow*/
SELECT people.name
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE flights.day = 29
AND flights.month = 7
AND flights.year = 2023
AND airports.city = 'Fiftyville';

/*Joining all and getting the closest airplane travell*/
SELECT people.name, flights.hour
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE flights.day = 29
AND flights.month = 7
AND flights.year = 2023
AND airports.city = 'Fiftyville'
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.year = 2023
AND phone_calls.day = 28
AND phone_calls.month = 7
AND phone_calls.year = 2023
AND phone_calls.duration <= 60
AND people.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND hour = 10
    AND minute <= 25
    AND minute >= 15
    AND activity = 'exit'
)
ORDER BY flights.hour ASC
LIMIT 1;

/*Getting the destination from rubbers flight*/
SELECT airports.city
FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE people.name = 'Bruce'
AND flights.day = 29
AND flights.month = 7
AND flights.year = 2023;

/*Getting the acomplice*/
SELECT people.name
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.day = 28
AND phone_calls.month = 7
AND phone_calls.year = 2023
AND phone_calls.duration <= 60
AND phone_calls.caller = (SELECT phone_number FROM people WHERE name = 'Bruce');

