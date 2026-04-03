#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

	//Music class
class Music {
private:
	string title;
	string artist;
	string album;
	int year;
public:
	// 생성자
	Music(string title, string artist, string album, int year) {
		this->title = title;
		this->artist = artist;
		this->album = album;
		this->year = year;
	}
	// Getters
	string getTitle() { return title; }
	string getArtist() { return artist; }
	string getAlbum() { return album; }
	int getYear() { return year; }
};

// MusicStreamingService Class
class MusicStreamingService {
private:
	string serviceName;
	vector<Music> musicList;
public:
	MusicStreamingService(string serviceName) {
		this->serviceName = serviceName;
	}
	// Music 객체를 service에 추가
	void addMusic(string title, string artist, string album, int year) {
		Music newMusic(title, artist, album, year);
		musicList.push_back(newMusic);
		cout << title << " by " << artist << " added to " << serviceName << endl;
	}
	// Title로 검색하기
	Music* serachByTitle(string title) {
		for (int i = 0; i < musicList.size(); i++) {
			if (musicList[i].getTitle() == title)
				return &musicList[i];
		}
		return NULL;
	}
};