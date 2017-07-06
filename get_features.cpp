// from http://dlib.net/face_landmark_detection_ex.cpp.html

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

int main(int argc, char** argv) {
    try {
        // takes in shape model file and a list of images to process_file
        // takes file names in as command line arguments
        if (argc == 1) {
            cout << "Call this program like this:" << endl;
            cout << "./face_landmark_detection_ex shape_predictor_68_face_landmarks.dat faces/*.jpg" << endl;
            cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
            cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
            return 0;
        }

        // get frontal face detector to find the face in the imageio
        frontal_face_detector detector = get_frontal_face_detector();

        // get shape predictor to predict face landmark positions given an image and
        // a face bounding box
        shape_predictor sp;
        // ???
        deserialize(argv[1]) >> sp;

        image_window win, win_faces;
        // Loop over all images provided in command line
        for (int i = 2; i < argc; ++i) {
            cout << "processing image " << argv[i] << endl;
            array2d<rgb_pixel> img;
            load_image(img, argv[i]);
            // make image larger
            pyramid_up(img);

            // get list of bounding boxes aroundf all the faces in the image
            std::vector<rectangle> dets = detector(img);
            cout << "Number of faces detected: " << dets.size() << endl;

            // get pose etimation of each face detected
            std::vector<full_object_detection> shapes;
            for (unsigned long j; j < dets.size(); ++j) {
                full_object_detection shape = sp(img, dets[j]);
                cout << "number of parts: " << shape.num_parts() << endl;
                cout << "pixel position of first part:  " << shape.part(0) << endl;
                cout << "pixel position of second part: " << shape.part(1) << endl;
                shapes.push_back(shape);
            }
            // view face poses on screen
            win.clear_overlay();
            win.set_image(img);
            win.add_overlay(render_face_detections(shapes));

            // extract copies of each face that are cropped rotated upright,
            // and scaled to a standard size
            dlib::array<array2d<rgb_pixel> > face_chips;
            extract_image_chips(img, get_face_chip_details(shapes), face_chips);
            win_faces.set_image(tile_images(face_chips));

            cout << "Hit enter to process the next image..." << endl;
            cin.get();
        }
    }
    catch (exception& e) {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}
