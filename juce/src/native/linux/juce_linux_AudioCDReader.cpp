/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

// (This file gets included by juce_linux_NativeCode.cpp, rather than being
// compiled on its own).
#if JUCE_INCLUDED_FILE && JUCE_USE_CDREADER

#if JUCE_USE_LIBCDIO
 static driver_id_t juce_cdio_driver_id = DRIVER_DEVICE;#endif

//==============================================================================
AudioCDReader::AudioCDReader (const String& deviceName_)
    : AudioFormatReader (0, T("CD Audio"))
{
#if JUCE_USE_LIBCDIO
    lastIndex = -1;
    deviceName = deviceName_;
    handle = cdio_open ((const char*) deviceName_, driver_id);
    
    if (handle)
    {
        cdio_get_media_changed (handle);
    }
#endif
}

const StringArray AudioCDReader::getAvailableCDNames()
{
    StringArray names;

#if JUCE_USE_LIBCDIO
    char **ppsz_cdda_drives = NULL;
    char **ppsz_all_cd_drives = cdio_get_devices_ret (&juce_cdio_driver_id);

    if (ppsz_all_cd_drives)
    {
        ppsz_cdda_drives = cdio_get_devices_with_cap (ppsz_all_cd_drives, CDIO_FS_AUDIO, false);
        if (! ppsz_cdda_drives || ! ppsz_cdda_drives[0])
        {
            fprintf (stderr, "Can't find a CD-ROM drive with a CD-DA in it\n");
        }
        else
        {
            int deviceIndex = 0;
            
            while (ppsz_cdda_drives [deviceIndex] != 0)
            {
                names.add (String (ppsz_cdda_drives [deviceIndex]));

                deviceIndex++;
            }
    
            cdio_free_device_list (ppsz_cdda_drives);
        }

        cdio_free_device_list (ppsz_all_cd_drives);
    }
#endif 


    return names;
}

AudioCDReader* AudioCDReader::createReaderForCD (const int index)
{
    AudioCDReader* reader = 0;

#if JUCE_USE_LIBCDIO
    char **ppsz_cdda_drives = NULL;
    char **ppsz_all_cd_drives = cdio_get_devices_ret (&juce_cdio_driver_id);

    if (ppsz_all_cd_drives)
    {
        ppsz_cdda_drives = cdio_get_devices_with_cap (ppsz_all_cd_drives, CDIO_FS_AUDIO, false);
        if (! ppsz_cdda_drives || ! ppsz_cdda_drives[0])
        {
            fprintf (stderr, "Can't find a CD-ROM drive with a CD-DA in it\n");
        }
        else
        {
            int deviceIndex = 0;
            
            while (ppsz_cdda_drives [deviceIndex] != 0)
            {
                if (index == deviceIndex)
                {
                    reader = new AudioCDReader (String (ppsz_cdda_drives [deviceIndex]));
                    break;
                }

                deviceIndex++;
            }
    
            cdio_free_device_list (ppsz_cdda_drives);
        }

        cdio_free_device_list (ppsz_all_cd_drives);
    }
#endif

    return reader;
}

AudioCDReader::~AudioCDReader()
{
#if JUCE_USE_LIBCDIO
    if (handle) {
        cdio_audio_stop (handle);
        cdio_destroy (handle);
    }
#endif
}

void AudioCDReader::refreshTrackLengths()
{
}

bool AudioCDReader::readSamples (int** destSamples, int numDestChannels, int startOffsetInDestBuffer,
                                 int64 startSampleInFile, int numSamples)
{
#if JUCE_USE_LIBCDIO
    int blocks;
    
    if (handle && handle->op.read_audio_sectors)
        (handle->op.read_audio_sectors) (handle->env, destSamples, lastIndex, blocks);
        
    lastIndex += blocks;
    
#endif


    return false;
}

bool AudioCDReader::isCDStillPresent() const
{
#if JUCE_USE_LIBCDIO
    if (handle)
        return cdio_get_media_changed (handle) == 0;
#endif

    return false;
}

int AudioCDReader::getNumTracks() const
{
#if JUCE_USE_LIBCDIO
    if (handle)
        return cdio_get_num_tracks (handle);
#endif

    return 0;
}

int AudioCDReader::getPositionOfTrackStart (int trackNum) const
{
    int offset = 0;

#if JUCE_USE_LIBCDIO
    if (handle)
    {
        cdio_subchannel_t sub;
        if( DRIVER_OP_SUCCESS == cdio_audio_read_subchannel (handle, &sub) )
        {
            if ((sub.audio_status != CDIO_MMC_READ_SUB_ST_PAUSED) &&
                (sub.audio_status != CDIO_MMC_READ_SUB_ST_PLAY))
            {
                return -1;
            }

            offset = cdio_msf_to_lba (& sub.abs_addr);
            // i_offset = cdio_msf_to_lba ((&sub.rel_addr));
        }
    }
#endif

    return offset;
}

bool AudioCDReader::isTrackAudio (int trackNum) const
{
#if JUCE_USE_LIBCDIO
    if (handle && handle->op.get_track_format)
        return handle->op.get_track_format (handle->env, trackNum) == TRACK_FORMAT_AUDIO;
#endif

    return false;
}

void AudioCDReader::enableIndexScanning (bool b)
{
}

int AudioCDReader::getLastIndex() const
{
#if JUCE_USE_LIBCDIO
    return lastIndex;
#else
    return 0;
#endif
}

const Array<int> AudioCDReader::findIndexesInTrack (const int trackNumber)
{
    return Array<int>();
}

int AudioCDReader::getCDDBId()
{
    return 0;
}

#endif
