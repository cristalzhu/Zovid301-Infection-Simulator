ALTER TABLE census
ADD COLUMN score NUMERIC;

/*drop table q3;*/

create table q3(
	id_Number BIGINT,
    vital_cap NUMERIC,
    metabolism NUMERIC,
    exam_date text,
    PRIMARY KEY  (id_Number)
);

/*SELECT DATA_TYPE FROM INFORMATION_SCHEMA.COLUMNS 
WHERE table_name = 'positive_physical_exam' AND COLUMN_NAME = 'exam_date';*/

select * from q3;

insert into q3  
select id_Number,vital_cap, metabolism, exam_date
						from positive_cases as p, positive_physical_exam as o
						where p.case_Number = o.case_Number;


insert into patients_physical_exam select * from q3;

select * from patients_physical_exam;

update census 
set score = (select 25*(vital_cap/5200 + metabolism/2800)
			from patients_physical_exam as alt
            where census.id_Number = alt.id_Number 
            order by alt.exam_date desc 
            limit 1) 
            + 25* ((1- abs(age-25)/75) + (1-abs(bmi-23)/30));
            
select * from census;

set @avscore = (select avg(score) 
			from census
			where score is not null);

select @avscore;

update census 
set score = @avscore
where score is null;
            

