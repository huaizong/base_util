

def decode_b(str):
    if not str:
        return str
    if str[0] == 'i':
        end_pos = str.find('e')
        if end_pos != -1:
            try:
                val = int(str[1:-1])
            except:
                val = None
            return val
    return None

print decode_b('i498e')
