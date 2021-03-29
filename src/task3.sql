select max(`row_Number`)
from audiences;

select max(seat_Number)
from audiences;

select  COUNT(*)
from audiences
where auditorium_Number=1;

select *
from audiences
where auditorium_Number=6;

insert into alert_info_1
select * from alert_info_2;

insert into alert_info_1
select * from alert_info_3;

insert into alert_info_1
select * from alert_info_4;

insert into alert_info_1
select * from alert_info_5;

insert into alert_info_1
select * from alert_info_6;

select Name, id_Number, ExposureTime
from alert_info_1;




