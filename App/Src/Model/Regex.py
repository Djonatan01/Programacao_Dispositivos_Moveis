import re

def emailRegex(_email):
  emailRegex = re.compile(
    r'([A-Za-z0-9]+[.-_])*[A-Za-z0-9]+@[A-Za-z0-9-]+(\.[A-Z|a-z]{2,})+'
  )
  return True if re.fullmatch(emailRegex, _email) else False

def contatoRegex(contato):
  contatoRegex = re.compile(
    r'^\(\d{2}\) (\d{0,5})-(\d{4})$'
  )
  return True if re.fullmatch(contatoRegex, contato) else False


