#ifndef FilmStripKnob_H
#define FilmStripKnob_H

class FilmStripKnob : public Slider
{
public:
	FilmStripKnob(Image* image, const int numFrames, const bool stripIsHorizontal)
		:   Slider("Film Strip Slider"),
		filmStrip(image),
		numFrames_(numFrames),
		isHorizontal_(stripIsHorizontal)
	{
		if(filmStrip)
		{
			setTextBoxStyle(NoTextBox, 0, 0, 0);
			setSliderStyle(RotaryVerticalDrag);
			frameHeight = filmStrip->getHeight() / numFrames_;
			frameWidth = filmStrip->getWidth();
			setRange(0.0f, 1.0f, 0.001f);
		}
	}

	void paint(Graphics& g)
	{
		if(filmStrip) {
			int value = (getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames_ - 1);
			if(isHorizontal_) {
				g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
					value * frameWidth, 0, frameWidth, frameHeight);
			} else {
				g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
					0, value * frameHeight, frameWidth, frameHeight);
			}
		}
	}

private:
	Image* filmStrip;
	const int numFrames_;
	const bool isHorizontal_;
	int frameWidth, frameHeight;
};

#endif

