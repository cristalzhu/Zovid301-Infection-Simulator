select * from census;



ALTER TABLE census
ADD COLUMN age NUMERIC;

update census set age = 2020-FLOOR((id_Number/100000000)MOD(10000));




