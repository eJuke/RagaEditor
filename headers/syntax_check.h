#ifndef SYNTAX_CHECK_H
#define SYNTAX_CHECK_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE


class Syntax : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Syntax(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct SyntaxRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<SyntaxRule> SyntaxRules;

    QRegExp commentStart;
    QRegExp commentEnd;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat quotPreFormat;
    QTextCharFormat quotBinFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat preProcessorFormat;
    QTextCharFormat includeFormat;
};

#endif // SYNTAX_CHECK_H
