"""decode bt torrent B encode data."""
def decode_b(data):
    """decode bt torrent B encode data."""
    if not data:
        return data
    if data[0] == 'i':
        end_pos = data.find('e')
        if end_pos != -1:
            try:
                val = int(data[1:-1])
            except TypeError:
                val = None
            return val
    return None

#print decode_b('i498e')
