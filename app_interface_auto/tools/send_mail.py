import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from email.mime.text import MIMEText
import smtplib
from tools.logconfig.logingconfig import loging
from email.header import Header


def send_mail(exception_e):
    '''
     发送异常信息至邮箱
    :param exception_e:
    :return:
    '''
    mail_host = "smtp.163.com"
    mail_user = "2323@163.com"
    mail_pass = "2323"
    sender = '23232@163.com'
    receivers = ['2323@qq.com', '2323@163.com', '2323.qin@test.com','232323.tan@test.com']

    message = MIMEText(exception_e, 'plain', 'utf-8')
    message['From'] = "23232@163.com"
    message['To'] = "232323.23232@test.com"
    subject = "自动化测试APP接口异常，注意查看"
    message['Subject'] = Header(subject, 'utf-8')
    smtpObj = smtplib.SMTP_SSL(mail_host, 465)

    smtpObj.login(mail_user, mail_pass)
    smtpObj.sendmail(sender, receivers, message.as_string())
    loging("邮件发送成功".center(100, "*"))
    smtpObj.quit()


def send_mail_result(msg):
    '''
    :param url:
    :param header:
    :param data:
    :param result:
    :return:
    '''
    mail_host = "smtp.163.com"
    mail_user = "2323@163.com"
    mail_pass = "2323"
    sender = '23232@163.com'
    receivers = ['2323@qq.com', '2323@163.com', '2323.qin@test.com', '232323.tan@test.com']

    message = MIMEText(msg, 'plain', 'utf-8')
    message['From'] = "23232@163.com"
    message['To'] = "232323.23232@test.com"
    subject = "自动化测试APP接口异常，注意及时查看并通知相关人员解决问题"
    message['Subject'] = Header(subject, 'utf-8')
    smtpObj = smtplib.SMTP_SSL(mail_host, 465)

    smtpObj.login(mail_user, mail_pass)
    smtpObj.sendmail(sender, receivers, message.as_string())
    loging("邮件发送成功".center(100, "*"))
    smtpObj.quit()
