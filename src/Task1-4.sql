ALTER TABLE audiences
ADD COLUMN test_result VARCHAR(6);

ALTER TABLE audiences
ADD COLUMN score NUMERIC;

select * from audiences;

update audiences
set test_result = (select result 
					from zovid12test
                    where zovid12test.id_Number = audiences.id_Number);


update audiences
set score = (select score 
					from census
                    where census.id_Number = audiences.id_Number);
