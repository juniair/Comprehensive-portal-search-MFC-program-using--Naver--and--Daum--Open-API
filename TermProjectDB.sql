# test �����ͺ��̽��� �����ϴ� ��쿡�� �����
drop database if exists TermProject_DB;
# test �����ͺ��̽��� �������� �ʴ� ��쿡�� �����
create database if not exists TermProject_DB;
# test�� id(����), name(���ڿ�), email(���ڿ�) �ʵ带 ���� data_info��� ���̺��� ������.
 CREATE TABLE if not exists TermProject_DB.key_word(
 keyword varchar(40),
 category char(40)
 );
INSERT INTO TermProject_DB.key_word
           VALUES('�ѱ��','��α�');
INSERT INTO TermProject_DB.key_word
           VALUES('�ƿ촩��','ī��');
INSERT INTO TermProject_DB.key_word
           VALUES('�ٻ�','��α�');
INSERT INTO TermProject_DB.key_word
           VALUES('����','������');
INSERT INTO TermProject_DB.key_word
           VALUES('�Ϳ�','��α�');
INSERT INTO TermProject_DB.key_word
           VALUES('mfc','��α�');







