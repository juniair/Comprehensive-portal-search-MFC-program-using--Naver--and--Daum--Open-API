# test 데이터베이스가 존재하는 경우에만 지우기
drop database if exists TermProject_DB;
# test 데이터베이스가 존재하지 않는 경우에만 만들기
create database if not exists TermProject_DB;
# test에 id(정수), name(문자열), email(문자열) 필드를 갖는 data_info라는 테이블을 만들자.
 CREATE TABLE if not exists TermProject_DB.key_word(
 keyword varchar(40),
 category char(40)
 );
INSERT INTO TermProject_DB.key_word
           VALUES('한기대','블로그');
INSERT INTO TermProject_DB.key_word
           VALUES('아우누리','카페');
INSERT INTO TermProject_DB.key_word
           VALUES('다산','블로그');
INSERT INTO TermProject_DB.key_word
           VALUES('스팀','웹문서');
INSERT INTO TermProject_DB.key_word
           VALUES('와우','블로그');
INSERT INTO TermProject_DB.key_word
           VALUES('mfc','블로그');







