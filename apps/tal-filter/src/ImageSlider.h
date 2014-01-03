#ifndef ImageSlider_H
#define ImageSlider_H

class ImageSlider : public Slider
{
public:

	// Curently only supports vertical sliders
	ImageSlider(Image* image, const int length)
		: Slider("Bitmap Slider"),
		imageKnob(image)
	{
		this->length = length;

		setTextBoxStyle(NoTextBox, 0, 0, 0);
		setSliderStyle(LinearVertical);

		frameHeight = imageKnob->getHeight();
		frameWidth = imageKnob->getWidth();

		setRange(0.0f, 1.0f, 0.001f);
	}

	void paint(Graphics& g)
	{
		double value = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
		g.drawImage(imageKnob, 0, (1.0f - value) * length, frameWidth, frameHeight,
			0, 0, frameWidth, frameHeight);
	}

private:
	Image* imageKnob;
	int length;
	int frameWidth, frameHeight;
};
#endif

