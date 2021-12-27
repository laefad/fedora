from sly import Lexer, Parser
import json

"""
EBNF of the syntax that this parser reads:

;; s-symbol         ::= "[^()\[\]= \n\t\r]+[^()\[\]=" \n\t\r]*" .
;; s-float          ::= "[-+]?[0-9]+.[0-9]+(E[-+]?[0-9]+)?" .
"""

"""
EXAMPLE:
(
    (let main (arg1, arg2) () )
)
"""

class Lex:
    """The class of the token. When the parser recognizes something, it writes it to the instance of this class.
 In data, it is always either NAME or NUMBER."""
    def __init__(self, data):
        self.data = data
        self.master = None
        self.slaves = []

    def __str__(self):
        return str(self.data)


class FedoraLexer(Lexer):
    """Lexer. Splits the input string into tokens"""
    tokens = {NAME, NUMBER, LPAREN, RPAREN}
    ignore = ' \t'

    # Tokens
    SYMBOL = r'[^()\[\]= \n\t\r]+[^()\[\]=" \n\t\r]*'   
    NUMBER = r'\d+'

    # Special symbols
    LPAREN = r'\('
    RPAREN = r'\)'

    # Ignored pattern
    ignore_newline = r'\n+'
    ignore_comments = r'\/\*.*\*\/'    # Ignore comments

    def error(self, t):
        self.index += 1


class FedoraParser(Parser):
    tokens = FedoraLexer.tokens

    precedence = (
        ('left', NAME),
    )

    def __init__(self):
        self.root = None
        self.errors = False
        self.is_comm = False

    def error(self, token):
        if not self.errors:
            print('Syntax error!!')
        self.errors = True

    @_('NAME')
    def expr(self, p):
        return p[0]

if __name__ == '__main__':
    """The main function of the program.
 Reads the information from the file and translates the tree of paired objects first to serializable, and then to Json"""
    lexer = FedoraLexer()
    parser = FedoraParser()

    text = 'programs/new_syntax.fe'
    if text:
        
        try:
            with open(text, 'r') as content_file:
                content = content_file.read()
                parser.parse(lexer.tokenize(content))
        except FileNotFoundError:
            print('File does not exist!')
        
        # if not parser.errors:
        #     root = parser.root
        #     serializable = root.get_serializable()
        #     print('Output JSON:')
        #     print(json.dumps(serializable, indent=1, ensure_ascii=False))
        # else:
        #     print('No output JSON due to syntax error.')