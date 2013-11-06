import email
from email.header import decode_header
from bs4 import BeautifulSoup, Comment

def get_mic_utf8_addr(addrs):
    utf8_addrs = []
    for name, addr in addrs:
        for name, decode in decode_header(name):
            if decode:
                name = name.decode(decode)
            utf8_addr = '%s <%s>' % (name, addr)
            utf8_addrs.append(utf8_addr)
    return utf8_addrs

def get_mic_mail_from(msg):
    froms = msg.get_all('from', [])
    all_addrs = email.utils.getaddresses(froms)
    return get_mic_utf8_addr(all_addrs)

def get_mic_mail_to(msg):
    tos = msg.get_all('to', [])
    ccs = msg.get_all('cc', [])
    resent_tos = msg.get_all('resent-to', [])
    resent_ccs = msg.get_all('resent-cc', [])
    all_addrs = email.utils.getaddresses(tos + ccs + resent_tos + resent_ccs)
    return get_mic_utf8_addr(all_addrs)

def parse_mail_mic():
    eml_obj = open("mic_test.eml", "r")
    msg = email.message_from_string(eml_obj.read())
    eml_obj.close()
    mic_info = {}
    mic_info['mailfrom'] = get_mic_mail_from(msg)
    mic_info['mailto'] = get_mic_mail_to(msg)
    mic_info['text_plain'] = []
    mic_info['text_html'] = []
    for part in msg.walk():
        if not part.is_multipart():
            if part.get_content_maintype() == 'text':
                if part.get_content_subtype() == 'plain':
                    text = part.get_payload(decode=True).strip()
                    if text != '':
                        mic_info['text_plain'].append(text)
                if part.get_content_subtype() == 'html':
                    eml_text = part.get_payload(decode=True).strip()
                    if eml_text != '':
                        soup = BeautifulSoup(eml_text)
                        comments = soup.findAll(text=lambda text:isinstance(text, Comment))
                        [comment.extract() for comment in comments]
                        #print soup.prettify()
                        print soup
                        #print soup.get_text()
                        mic_info['text_html'].append(soup.get_text())
                        #print soup
    #print mic_info


parse_mail_mic()
