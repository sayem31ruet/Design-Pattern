#include <iostream>
#include <string>
using namespace std;

// Target interface
class MediaPlayer
{
public:
    virtual void play(string audioType, string fileName) = 0;
    virtual ~MediaPlayer() {}
};

// Adaptee interface
class AdvancedMediaPlayer
{
public:
    virtual void playVlc(string fileName) = 0;
    virtual void playMp4(string fileName) = 0;
    virtual ~AdvancedMediaPlayer() {}
};

// Concrete Adaptee
class VlcPlayer : public AdvancedMediaPlayer
{
public:
    void playVlc(string fileName) override
    {
        cout << "Playing vlc file. Name: " << fileName << endl;
    }

    void playMp4(string fileName) override
    {
        // VlcPlayer cannot play mp4
    }
};

// Concrete Adaptee
class Mp4Player : public AdvancedMediaPlayer
{
public:
    void playVlc(string fileName) override
    {
        // Mp4Player cannot play vlc
    }

    void playMp4(string fileName) override
    {
        cout << "Playing mp4 file. Name: " << fileName << endl;
    }
};

// Adapter
class MediaAdapter : public MediaPlayer
{
private:
    AdvancedMediaPlayer *advancedPlayer;

public:
    MediaAdapter(string audioType)
    {
        if (audioType == "vlc")
        {
            advancedPlayer = new VlcPlayer();
        }
        else if (audioType == "mp4")
        {
            advancedPlayer = new Mp4Player();
        }
        else
        {
            advancedPlayer = nullptr;
        }
    }

    void play(string audioType, string fileName) override
    {
        if (audioType == "vlc")
        {
            advancedPlayer->playVlc(fileName);
        }
        else if (audioType == "mp4")
        {
            advancedPlayer->playMp4(fileName);
        }
    }

    ~MediaAdapter()
    {
        delete advancedPlayer;
    }
};

// Client
class AudioPlayer : public MediaPlayer
{
public:
    void play(string audioType, string fileName) override
    {
        if (audioType == "mp3")
        {
            cout << "Playing mp3 file. Name: " << fileName << endl;
        }
        else if (audioType == "vlc" || audioType == "mp4")
        {
            MediaAdapter *mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter->play(audioType, fileName);
            delete mediaAdapter;
        }
        else
        {
            cout << "Invalid media. " << audioType
                 << " format not supported" << endl;
        }
    }
};

int main()
{
    AudioPlayer audioPlayer;

    audioPlayer.play("mp3", "song.mp3");
    audioPlayer.play("mp4", "video.mp4");
    audioPlayer.play("vlc", "movie.vlc");
    audioPlayer.play("avi", "movie.avi");

    return 0;
}