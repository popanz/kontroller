#ifndef EU_TGCM_KONTROLLER_FILE_H
#define EU_TGCM_KONTROLLER_FILE_H

#include <QObject>

#include <QVector>

namespace eu
{
namespace tgcm
{
namespace kontroller
{

class File
{
	Q_GADGET
private:
	QString file_;
	QString filetype_;
	QString label_;
	QString type_;
	QString thumbnail_;
public:
	File() = default;

	~File() = default;

	File(File const&) = default;

	File(File&&) = default;

	File& operator=(File const&) = default;

	File& operator=(File&&) = default;

public:
	Q_PROPERTY(QString file READ file WRITE setFile)
	Q_PROPERTY(QString filetype READ filetype WRITE setFiletype)
	Q_PROPERTY(QString label READ label WRITE setLabel)
	Q_PROPERTY(QString type READ type WRITE setType)
	Q_PROPERTY(QString thumbnail READ thumbnail WRITE setThumbnail)


	QString file() const;
	QString filetype() const;
	QString label() const;
	QString type() const;
	QString thumbnail() const;

	void setFile(QString file);
	void setFiletype(QString filetype);
	void setLabel(QString label);
	void setType(QString type);
	void setThumbnail(QString thumbnail);

};

}
}
}

QDataStream& operator<<(QDataStream& stream, eu::tgcm::kontroller::File const& file);

QDataStream& operator>>(QDataStream& stream, eu::tgcm::kontroller::File& file);

Q_DECLARE_METATYPE(eu::tgcm::kontroller::File)

#endif // EU_TGCM_KONTROLLER_FILE_H
