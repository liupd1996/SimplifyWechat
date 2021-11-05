//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by Fernflower decompiler)
//

package org.opencv.wechat_qrcode;

import java.util.List;
import org.opencv.core.Mat;
import org.opencv.utils.Converters;

public class WeChatQRCode {
    protected final long nativeObj;

    protected WeChatQRCode(long addr) {
        this.nativeObj = addr;
    }

    public long getNativeObjAddr() {
        return this.nativeObj;
    }

    public static WeChatQRCode __fromPtr__(long addr) {
        return new WeChatQRCode(addr);
    }

    public WeChatQRCode(String detector_prototxt_path, String detector_caffe_model_path, String super_resolution_prototxt_path, String super_resolution_caffe_model_path) {
        this.nativeObj = WeChatQRCode(detector_prototxt_path, detector_caffe_model_path, super_resolution_prototxt_path, super_resolution_caffe_model_path);
    }

    public List<String> detectAndDecode(Mat img, List<Mat> points) {
        Mat points_mat = new Mat();
        List<String> retVal = detectAndDecode_0(this.nativeObj, img.nativeObj, points_mat.nativeObj);
        Converters.Mat_to_vector_Mat(points_mat, points);
        points_mat.release();
        return retVal;
    }

    public List<String> detectAndDecode(Mat img) {
        return detectAndDecode_1(this.nativeObj, img.nativeObj);
    }

    protected void finalize() throws Throwable {
        delete(this.nativeObj);
    }

    private static native long WeChatQRCode(String var0, String var1, String var2, String var3);

    private static native List<String> detectAndDecode_0(long var0, long var2, long var4);

    private static native List<String> detectAndDecode_1(long var0, long var2);

    private static native void delete(long var0);
}
