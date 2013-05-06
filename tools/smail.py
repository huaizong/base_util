#!/usr/bin/python
#encoding=utf-8
import sys
import smtplib
import mimetypes
from email import encoders
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import Header

def send_mail(to_list, sub, path):
    ctype, encoding = mimetypes.guess_type(path)
    me = '"huaizong"<work_test_whz@sina.cn>"'
    outer = MIMEMultipart()
    outer['From'] = me
    outer['To'] = ';'.join(to_list)
    outer['Subject'] = Header(sub, 'utf-8')
    outer.preamble = 'You will not see this in a MIME-aware mail reader.\n'
    maintype, subtype = ctype.split('/', 1)
    if maintype == 'text':
        fp = open(path)
        # Note: we should handle calculating the charset
        msg = MIMEText(fp.read(), _subtype=subtype)
        fp.close()
    else:
        fp = open(path, 'rb')
        msg = MIMEBase(maintype, subtype)
        msg.set_payload(fp.read())
        fp.close()
        # Encode the payload using Base64
        encoders.encode_base64(msg)
    outer.attach(msg)
    body_text = MIMEText(sub, 'plain', 'utf-8')
    outer.attach(body_text)
    try:
        s = smtplib.SMTP()
        s.connect('127.0.0.1')
        s.set_debuglevel(1)
        s.sendmail(me, to_list, outer.as_string())
        s.quit()
        return True
    except Exception, e:
        print str(e)
        return False

if __name__ == '__main__':
    if len(sys.argv) > 1:
        path =  sys.argv[1]
    else:
        path =  sys.argv[0]
    if send_mail(['work_test_whz@sina.cn'], 'test subject', path):
        print 'send succ' 
    else:
        print 'send fail'
