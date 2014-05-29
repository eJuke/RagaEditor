#include "headers/syntax_check.h"


Syntax::Syntax(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    SyntaxRule rule;

    keywordFormat.setForeground(QColor(230,102,34));
//    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\binclude\\b";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        SyntaxRules.append(rule);

    }

    singleLineCommentFormat.setForeground(QColor(60,255,0));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    SyntaxRules.append(rule);

    multiLineCommentFormat.setForeground(QColor(60,255,0));

    quotationFormat.setForeground(QColor(4,172,15));
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    SyntaxRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor(0,239,255));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    SyntaxRules.append(rule);

    commentStart = QRegExp("/\\*");
    commentEnd = QRegExp("\\*/");
}

void Syntax::highlightBlock(const QString &text)
{
    foreach (const SyntaxRule &rule, SyntaxRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStart.indexIn(text);

    while (startIndex >= 0)
    {

        int endIndex = commentEnd.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex + commentEnd.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStart.indexIn(text, startIndex + commentLength);
    }
}
