package com.mobilecontrol.client.qrscan;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.text.TextUtils;
import android.util.Log;
import android.view.KeyEvent;

import com.google.zxing.ResultPoint;
import com.google.zxing.client.android.BeepManager;
import com.journeyapps.barcodescanner.BarcodeCallback;
import com.journeyapps.barcodescanner.BarcodeResult;
import com.journeyapps.barcodescanner.DecoratedBarcodeView;
import com.mobilecontrol.client.R;

import java.util.List;

public class QRScannerActivity extends Activity {

    private static final String TAG = "QRScannerActivity";

    public static final String QR_SCAN_RESULT = "qr_scan_result";
    private static final long BEEP_DELAY = 150;

    private BeepManager beepManager;
    private DecoratedBarcodeView barcodeView;
    private Handler handler = new Handler();

    private BarcodeCallback callback = new BarcodeCallback() {
        @Override
        public void barcodeResult(final BarcodeResult result) {
            Log.d(TAG, "BarcodeCallback barcodeResult");
            beepManager.playBeepSoundAndVibrate();
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    String resultText = result.getText();
                    if (!TextUtils.isEmpty(resultText)) {
                        Log.d(TAG, "resultText: " + resultText);
                        Intent data = new Intent();
                        data.putExtra(QR_SCAN_RESULT, resultText);
                        setResult(RESULT_OK, data);
                    } else {
                        setResult(RESULT_CANCELED);
                    }
                    QRScannerActivity.this.finish();
                }
            }, BEEP_DELAY);

        }

        @Override
        public void possibleResultPoints(List<ResultPoint> resultPoints) {
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_qrscanner);

        barcodeView = (DecoratedBarcodeView) findViewById(R.id.barcode_scanner);
        barcodeView.decodeSingle(callback);

        beepManager = new BeepManager(this);
        beepManager.setBeepEnabled(true);
        beepManager.updatePrefs();
    }

    @Override
    protected void onResume() {
        super.onResume();
        barcodeView.resume();
        beepManager.updatePrefs();
    }

    @Override
    protected void onPause() {
        super.onPause();
        barcodeView.pause();
        beepManager.close();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            return super.onKeyDown(keyCode, event);
        } else {
            return barcodeView.onKeyDown(keyCode, event) || super.onKeyDown(keyCode, event);
        }
    }
}
