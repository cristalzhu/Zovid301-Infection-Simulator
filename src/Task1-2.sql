select * from census;

select * from patient_info;

ALTER TABLE census
ADD COLUMN bmi NUMERIC;

                                
update census as c
set bmi =  (select weight_kg/((height_cm/100) *(height_cm/100)) 
			from patient_info as p
			where p.id_Number = c.id_Number);



