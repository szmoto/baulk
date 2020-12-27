//
#ifndef BAULK_ZIP_INTERNAL_HPP
#define BAULK_ZIP_INTERNAL_HPP
#include <bela/path.hpp>
#include <zip.hpp>

namespace baulk::archive::zip {
// https://pkware.cachefly.net/webdocs/casestudies/APPNOTE.TXT
// https://en.wikipedia.org/wiki/ZIP_(file_format)
// https://en.wikipedia.org/wiki/Comparison_of_file_archivers
// https://en.wikipedia.org/wiki/List_of_archive_formats
constexpr int fileHeaderSignature = 0x04034b50;
constexpr int directoryHeaderSignature = 0x02014b50;
constexpr int directoryEndSignature = 0x06054b50;
constexpr int directory64LocSignature = 0x07064b50;
constexpr int directory64EndSignature = 0x06064b50;
constexpr uint32_t dataDescriptorSignature = 0x08074b50; // de-facto standard; required by OS X Finder
constexpr uint32_t fileHeaderLen = 30;                   // + filename + extra
constexpr int directoryHeaderLen = 46;                   // + filename + extra + comment
constexpr int directoryEndLen = 22;                      // + comment
constexpr int dataDescriptorLen = 16;   // four uint32: descriptor signature, crc32, compressed size, size
constexpr int dataDescriptor64Len = 24; // descriptor with 8 byte sizes
constexpr int directory64LocLen = 20;   //
constexpr int directory64EndLen = 56;   // + extra

// Constants for the first byte in CreatorVersion.
constexpr int creatorFAT = 0;
constexpr int creatorUnix = 3;
constexpr int creatorNTFS = 11;
constexpr int creatorVFAT = 14;
constexpr int creatorMacOSX = 19;

// Version numbers.
constexpr int zipVersion20 = 20; // 2.0
constexpr int zipVersion45 = 45; // 4.5 (reads and writes zip64 archives)

// Limits for non zip64 files.
constexpr auto uint16max = (std::numeric_limits<uint16_t>::max)();
constexpr auto uint32max = (std::numeric_limits<uint32_t>::max)();

// Extra header IDs.
//
// IDs 0..31 are reserved for official use by PKWARE.
// IDs above that range are defined by third-party vendors.
// Since ZIP lacked high precision timestamps (nor a official specification
// of the timezone used for the date fields), many competing extra fields
// have been invented. Pervasive use effectively makes them "official".
//
// See http://mdfs.net/Docs/Comp/Archiving/Zip/ExtraField
constexpr int zip64ExtraID = 0x0001;       // Zip64 extended information
constexpr int ntfsExtraID = 0x000a;        // NTFS
constexpr int unixExtraID = 0x000d;        // UNIX
constexpr int extTimeExtraID = 0x5455;     // Extended timestamp
constexpr int infoZipUnixExtraID = 0x5855; // Info-ZIP Unix extension
constexpr int winzipAesExtraID = 0x9901;   // winzip AES Extra Field

inline bool IsSuperficialPath(std::string_view sv) {
  auto pv = bela::SplitPath(sv);
  return pv.size() <= 3;
}

} // namespace baulk::archive::zip

#endif