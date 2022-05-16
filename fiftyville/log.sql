-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

SELECT name FROM people
  JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
  WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15 AND activity = "exit";

SELECT name FROM people
  JOIN bank_accounts ON bank_accounts.person_id = people.id
  JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
  WHERE year = 2021 AND month = 7 AND day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw";

SELECT flights.id, full_name, city, flights.hour, flights.minute FROM airports
  JOIN flights ON airports.id = flights.destination_airport_id WHERE flights.origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29 ORDER BY flights.hour, flights.minute;

SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat FROM people
  JOIN passengers ON people.passport_number = passengers.passport_number
  JOIN flights ON passengers.flight_id = flights.id
 WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8 AND flights.minute = 20 ORDER BY passengers.passport_number;

SELECT name, phone_calls.duration FROM people
  JOIN phone_calls ON people.phone_number = phone_calls.caller
 WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60 ORDER BY phone_calls.duration;

SELECT name, phone_calls.duration FROM people
  JOIN phone_calls ON people.phone_number = phone_calls.receiver
 WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60 ORDER BY phone_calls.duration;

SELECT phone_number FROM people WHERE name = "Bruce";

SELECT name FROM people WHERE phone_number = (
  SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533");