-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE street LIKE "HUMPHREY STREET";
SELECT * FROM interviews WHERE transcript LIKE "%bakery%";
--Lisence plates of theif car possible
SELECT license_plate from bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 07 AND hour = 10 AND minute < 30 AND activity = "exit";
--Phone number possibilities
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60;
-- ATM transactions at proper ATM
SELECT * FROM atm_transactions WHERE atm_location LIKE "Leggett Street" AND year = 2021 AND month = 7 AND day = 28;
--Flights
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour;
--Possible suspects based on phone and plate
SELECT * FROM people WHERE license_plate IN (SELECT license_plate from bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 07 AND hour = 10 AND minute < 30 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60);
--Suspects based on ATM
SELECT person_id from bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett Street" AND year = 2021 AND month = 7 AND day = 28);
--Suspects based on phone, plate, and ATM
SELECT * FROM people WHERE license_plate IN (SELECT license_plate from bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 07 AND hour = 10 AND minute < 30 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60) AND id IN (SELECT person_id from bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett Street" AND year = 2021 AND month = 7 AND day = 28));

-- Final name
 SELECT people.name FROM people, passengers WHERE passengers.passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate from bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 07 AND hour = 10 AND minute < 30 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60) AND id IN (SELECT person_id from bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett Street" AND year = 2021 AND month = 7 AND day = 28))) AND flight_id = 36 AND people.passport_number = passengers.passport_number;

 --Accomplice call
 SELECT * FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60 AND caller LIKE "(367) 555-5533";

 --Accomplice name
 SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60 AND caller LIKE "(367) 555-5533");