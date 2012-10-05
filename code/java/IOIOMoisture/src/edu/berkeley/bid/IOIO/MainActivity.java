package edu.berkeley.bid.IOIO;

import ioio.lib.api.AnalogInput;
import ioio.lib.api.DigitalOutput;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.util.BaseIOIOLooper;
import ioio.lib.util.IOIOLooper;
import ioio.lib.util.android.IOIOActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.ToggleButton;

public class MainActivity extends IOIOActivity {
	private TextView sensorReading_;
	private ToggleButton waterIt_;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        sensorReading_ = (TextView)findViewById(R.id.Wateriness);
        waterIt_ = (ToggleButton)findViewById(R.id.WaterIt);

        enableUi(false);
    }
	
	class Looper extends BaseIOIOLooper {
		private AnalogInput input_;
		private DigitalOutput led_;
		float reading_ = 0;

		@Override
		public void setup() throws ConnectionLostException {
			try {
				input_ = ioio_.openAnalogInput(40);
				led_ = ioio_.openDigitalOutput(0, true);
				enableUi(true);
			} catch (ConnectionLostException e) {
				enableUi(false);
				throw e;
			}
		}
		
		@Override
		public void loop() throws ConnectionLostException {
      led_.write(!waterIt_.isChecked());
      setText("Wateriness: " + Float.toString(reading_));
		  try {
				reading_ = input_.read();
			} catch (InterruptedException e) {
				ioio_.disconnect();
			}
		}
	}

	@Override
	protected IOIOLooper createIOIOLooper() {
		return new Looper();
	}

	private void enableUi(final boolean enable) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				waterIt_.setEnabled(enable);
			}
		});
	}
	
	private void setText(final String str) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				sensorReading_.setText(str);
			}
		});
	}
}