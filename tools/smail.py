#!/usr/bin/python
#encoding=utf-8
import smtplib
from email.mime.text import MIMEText
def send_mail(to_list, sub, content):
    msg = MIMEText(content)
    me = '"huaizong"<work_test_whz@sina.cn>"'
    msg['Subject'] = sub
    msg['From'] = me
    msg['To'] = ';'.join(to_list)
    try:
        s = smtplib.SMTP()
        s.connect('ali')
        s.sendmail(me, to_list, msg.as_string())
        s.quit()
        return True
    except Exception, e:
        print str(e)
        return False

if __name__ == '__main__':
    if send_mail(['work_test_whz@sina.cn'], 'test subject', 'test content'):
        print 'send succ' 
    else:
        print 'send fail'
