#pragma once


#include <list>

#include "StringUtils.hpp"
#include "CommonTime.hpp"
#include "FFStream.hpp"
#include "RinexNavBase.hpp"
#include "TrajectoryBase.hpp"
#include "TrajectoryStream.hpp"
#include "Position.hpp"
#include "TrajectoryHeader.hpp"

#include "I_GINA_writer.hpp"

namespace GINAParser
{
	/// @ingroup FileHandling
	//@{

	/**
	* This class models a RINEX NAV record.
	*
	* \sa rinex_nav_test.cpp and rinex_nav_read_write.cpp for examples.
	* \sa gpstk::RinexNavHeader and gpstk::RinexNavStream classes.
	*/
	class TrajectoryData : public TrajectoryBase
	{
	public:
		/**
		* Constructor
		* @warning CHECK THE PRNID TO SEE IF THIS DATA IS
		*  VALID BEFORE USING!!
		*/
		TrajectoryData() {};

		/// destructor
		virtual ~TrajectoryData() {}

		// The next four lines is our common interface
		/// RinexNavData is "data" so this function always returns true.
		virtual bool isData() const { return true; }

		/// Outputs the record to the FFStream \a s.
		virtual void reallyPutRecord(gpstk::FFStream& s) const
			throw(std::exception, gpstk::FFStreamError,
				gpstk::StringUtils::StringException);

		/**
		* This function retrieves a RINEX NAV record from the given FFStream.
		* If an error is encountered in reading from the stream, the stream
		* is returned to its original position and its fail-bit is set.
		* @throws StringException when a StringUtils function fails
		* @throws FFStreamError when exceptions(failbit) is set and
		*  a read or formatting error occurs.  This also resets the
		*  stream to its pre-read position.
		*/
		virtual void reallyGetRecord(gpstk::FFStream& s)
			throw(std::exception, gpstk::FFStreamError,
				gpstk::StringUtils::StringException);
	
		bool compare(const TrajectoryData&) const;
		bool operator==(const TrajectoryData& ) const;
		bool operator!=(const TrajectoryData& ) const;
		

		TrajectoryData& operator+=(gpstk::Position&);
		TrajectoryData& operator=(gpstk::Position&);
		TrajectoryData& operator=(TrajectoryData&);

		gpstk::Position::CoordinateSystem coorSys = gpstk::Position::CoordinateSystem::Unknown;
		gpstk::TimeSystem timeSys = gpstk::TimeSystem::Systems::Unknown;
		gpstk::Position pos;
		gpstk::CommonTime time;

		double attitude[3];
		
		TrajectoryData& operator=(I_TrajectoryData&);
	
		double getGPSWeek(void);
		double getGPSToW(void);

		static const string TrajectoryData::startofDataTag;
		
	private:
		TrajectoryStream* strm;

		void TrajectoryData::parseLine(std::string& currentLine) 
			throw(gpstk::StringUtils::StringException, gpstk::FFStreamError);

	};  // class RinexNavData

		//@}
} // namespace



