import sys
from tools.file_system_path import file_system_path

sys.path.append(file_system_path())
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.application import MIMEApplication
import smtplib
import os
from tools.logconfig.logingconfig import loging


def send_mail(file_new):
    mail_host = 'smtp.163.com'
    user = '123@163.com'
    password = '123'
    sender = '3434@163.com'

    receiver = ['3434324@qq.com', '2323232@qq.com']
    msg = MIMEMultipart()
    msg['from'] = '3434@163.com'
    msg['to'] = '34343434@qq.com'
    subject = '自动化测试报告'
    msg['subject'] = subject
    content = open(file_new, 'rb').read()
    txt = MIMEText(content, 'html', 'utf-8')
    msg.attach(txt)

    # 添加附件地址
    part = MIMEApplication(content)
    file = file_new.split("\\")
    file_name = file[len(file) - 1]
    part['Content-Disposition'] = 'attachment;filename = ' + file_name
    msg.attach(part)

    smtp = smtplib.SMTP()
    smtp.connect(mail_host, '25')
    smtp.login(user, password)
    for rec in receiver:
        smtp.sendmail(sender, rec, msg.as_string())
    loging("邮件发送成功！")
    smtp.quit()


def new_report(testreport):
    lists = os.listdir(testreport)
    lists.sort(key=lambda fn: os.path.getatime(testreport + "\\" + fn))
    file_new = os.path.join(testreport, lists[-1])
    loging(file_new)
    return file_new
