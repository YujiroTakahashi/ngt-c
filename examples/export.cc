#include <stdlib.h>
#include <iostream>
#include <sstream>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include <croco/ngt/Index.h>

struct membuf : std::streambuf {
    membuf(char* base, std::size_t n) {
        std::cout << n << "<<<\n";
        this->setg(base, base, base + n);
    }
};

int main(int argc, char **argv)
{
    if (3 > argc) {
        std::cout << "./export_ngt [user name] [user passwd]\n";
        exit(1);
    }

    std::vector<float> data = {
        0.021829, -0.014656, -0.024689, -0.10769, -0.0073684, -0.022597, 0.025262, 0.013813, 0.046709, -0.037274, 
        0.0015581, 0.036055, -0.01992, -0.031109, 0.031879, -0.011737, -0.062557, -0.031275, -0.039937, 0.034292, 
        0.017959, -0.042308, -0.02949, -0.008628, 0.020521, -0.064644, 0.037932, 0.019465, 0.020891, -0.053764, 
        -0.0035911, -0.015461, -0.065987, -0.071607, -0.046855, -0.034706, -0.041453, -0.070162, 0.071203, -0.047257, 
        0.026626, 0.039486, 0.026613, -0.041279, -0.042622, -0.018237, 0.023128, 0.027951, 0.025845, 0.015641, 
        -0.043905, 0.02942, -0.012245, 0.062556, 0.014416, -0.014394, -0.015112, 0.030043, -0.039814, 0.026466, 
        0.0052573, 0.025375, 0.0026063, 0.038632, -0.030029, -0.016044, 0.043741, 0.038885, 0.08555, -0.062577, 
        0.034098, 0.037711, -0.059571, 0.052436, -0.06068, 0.00023655, 0.0073647, 0.031876, -0.044448, 0.04694, 
        -0.024007, 0.066073, 0.025459, 0.15372, 0.0046967, 0.010413, 0.027904, 0.045138, -0.026914, -0.040564, 
        0.0029196, -0.02971, -0.039609, 0.045475, -0.0027469, -0.012581, -0.026742, 0.0021271, 0.085099, -0.059727, 
        0.02112, -0.03748, 0.02767, 0.062495, -0.05034, -0.081659, -0.036758, 0.052467, -0.021049, -0.052423, 
        -0.029815, -0.061481, -0.0089195, 0.052777, -0.05628, 0.018658, 0.050899, 0.060684, -0.067914, 0.050957, 
        -0.050156, 0.03152, -0.043569, 0.060886, -0.075258, -0.078253, 0.10029, -0.030497, -0.065022, 0.096127, 
        -0.020996, -0.049704, -0.027016, 0.053992, 0.00618, -0.058062, 0.065172, -0.031387, -0.013745, -0.078324, 
        -0.054965, 0.049138, -0.44507, -0.03377, 0.027301, -0.033449, 0.058108, 0.066885, -0.058807, 0.049191, 
        -0.066582, -0.028249, 0.055656, -0.041904, -0.060864, 0.055212, -0.06419, -0.080575, 0.074898, -0.090375, 
        0.033885, 0.013567, 0.0055847, -0.021733, 0.021884, -0.090772, -0.089044, 0.066501, -0.088693, 0.051331, 
        0.075103, 0.059359, 0.083976, 0.04961, 0.043419, 0.035661, -0.031751, 0.066279, 0.080812, 0.072829, 
        0.018679, 0.024251, 0.018446, -0.020374, 0.056647, 0.013649, 0.061512, 0.03461, -0.017127, 0.018827, 
        -0.014068, 0.046948, 0.0068629, -0.032489, -0.055795, 0.0096172, -0.0081729, 0.053734, -0.038393, 0.048037, 
        -0.031099, 0.070994, 0.044808, 0.052563, 0.042756, -0.026406, -0.061937, 0.023657, 0.11202, -0.009432, 
        0.057411, -0.026274, 0.046649, 0.039389, 0.034656, -0.038465, 0.074201, 0.030769, 0.034352, 0.039312, 
        -0.026512, 0.048607, -0.021153, 0.043541, -0.0523, 0.025062, 0.027234, -0.043122, -0.065886, -0.031022, 
        0.019351, -0.049748, -0.026454, -0.042663, 0.0034103, 0.022363, -0.011924, -0.0089488, -0.0090182, -0.0063537, 
        0.042688, 0.090824, -0.063852, -0.050924, 0.12672, 0.043274, -0.022456, -0.025898, -0.039756, -0.034698, 
        -0.033428, -0.058688, 0.083287, 0.072529, -0.02971, -0.060592, -0.016767, -0.059398, 0.046803, 0.023415, 
        0.043465, 0.0096912, -0.048066, -0.087387, -0.049654, 0.054141, 0.063353, 0.010249, 0.0058976, -0.04909, 
        -0.052516, -0.015424, -0.061641, 0.023504, -0.015732, -0.057549, 0.058291, -0.093303, 0.020311, -0.086382, 
        -0.012424, 0.06798, -0.035906, 0.055811, 0.092382, 0.019811, 0.088307, -0.040228, 0.020058, -0.016528, 
        -0.056641, 0.10346, -0.071588, 0.011382, 0.0092847, 0.036896, -0.039176, 0.045547, 0.041473, -0.045585
    };
    std::vector<float> query = {
        0.021593, -0.013728, -0.025222, -0.10652, -0.0072144, -0.023198, 0.025298, 0.013533, 0.046633, -0.037416, 
        0.0015004, 0.035886, -0.019384, -0.03127, 0.03192, -0.01173, -0.062024, -0.030848, -0.039921, 0.034673, 
        0.01716, -0.04269, -0.02971, -0.0082751, 0.02036, -0.064246, 0.037503, 0.019448, 0.020177, -0.053324, 
        -0.0039145, -0.015519, -0.065727, -0.070551, -0.046416, -0.034357, -0.041681, -0.068942, 0.071483, -0.047291, 
        0.026799, 0.03936, 0.026494, -0.041393, -0.043053, -0.017916, 0.023624, 0.027435, 0.025567, 0.015203, 
        -0.043387, 0.029254, -0.012582, 0.062093, 0.013701, -0.014624, -0.01548, 0.029065, -0.039762, 0.025926, 
        0.0052232, 0.02543, 0.0032234, 0.038302, -0.029415, -0.016186, 0.043645, 0.038234, 0.084588, -0.062317, 
        0.034106, 0.037469, -0.059511, 0.051891, -0.061112, -0.00018574, 0.0073689, 0.031974, -0.044364, 0.046784, 
        -0.023643, 0.065515, 0.025522, 0.15232, 0.0046407, 0.010817, 0.028013, 0.044813, -0.027235, -0.040301, 
        0.0029193, -0.029488, -0.039612, 0.045216, -0.0028404, -0.012544, -0.026839, 0.0022989, 0.084118, -0.059528, 
        0.020251, -0.037436, 0.027523, 0.062394, -0.050231, -0.081399, -0.036514, 0.052345, -0.020397, -0.052121, 
        -0.02965, -0.060396, -0.0089224, 0.052535, -0.055856, 0.018505, 0.050422, 0.060044, -0.067418, 0.050471, 
        -0.04957, 0.031262, -0.04317, 0.060269, -0.074957, -0.077933, 0.1003, -0.030309, -0.065373, 0.095403, 
        -0.020841, -0.049816, -0.026832, 0.05389, 0.006716, -0.057391, 0.065065, -0.030653, -0.013675, -0.077705, 
        -0.054888, 0.048337, -0.44027, -0.033704, 0.027524, -0.033761, 0.057897, 0.066164, -0.058839, 0.048877, 
        -0.06652, -0.028238, 0.055454, -0.041595, -0.060659, 0.054943, -0.063566, -0.07995, 0.074463, -0.089579, 
        0.033741, 0.013757, 0.0054379, -0.021389, 0.021708, -0.090225, -0.088741, 0.066036, -0.087915, 0.051464, 
        0.074936, 0.05886, 0.083432, 0.049463, 0.043253, 0.035571, -0.031334, 0.065403, 0.08047, 0.072292, 
        0.019278, 0.023993, 0.018175, -0.019689, 0.056303, 0.013778, 0.060594, 0.034988, -0.017293, 0.01872, 
        -0.014209, 0.046576, 0.0062162, -0.031477, -0.055581, 0.0096534, -0.0082444, 0.053578, -0.038052, 0.047378, 
        -0.030833, 0.070358, 0.044447, 0.051635, 0.042405, -0.025837, -0.061336, 0.023398, 0.11149, -0.0093883, 
        0.057212, -0.026332, 0.046692, 0.039131, 0.034849, -0.038315, 0.073418, 0.030626, 0.034411, 0.039285, 
        -0.026074, 0.047913, -0.021243, 0.042853, -0.052451, 0.025301, 0.027506, -0.043104, -0.064948, -0.03121, 
        0.019469, -0.049536, -0.026087, -0.041789, 0.003629, 0.021902, -0.012119, -0.0088071, -0.0087212, -0.0070248, 
        0.042598, 0.090651, -0.06351, -0.050883, 0.1259, 0.043926, -0.02241, -0.025324, -0.039169, -0.035672, 
        -0.033712, -0.058824, 0.08323, 0.072274, -0.029799, -0.060807, -0.017491, -0.059349, 0.046371, 0.022585, 
        0.042935, 0.0096756, -0.04805, -0.087372, -0.049599, 0.053633, 0.062058, 0.010607, 0.0057323, -0.047695, 
        -0.052099, -0.015673, -0.062431, 0.023462, -0.016697, -0.057025, 0.057897, -0.091861, 0.019719, -0.08604, 
        -0.012648, 0.066788, -0.035954, 0.054719, 0.091156, 0.019246, 0.08825, -0.040683, 0.019947, -0.016102, 
        -0.056239, 0.102, -0.07049, 0.011525, 0.0085731, 0.03665, -0.038483, 0.044468, 0.04081, -0.044913
    };

    croco::Index index;
    index.create(300);
    index.batchInsert(data);
    index.batchInsert(query);
    index.exportIndex();

    try {
        sql::Driver *driver = get_driver_instance();
        sql::Connection *con = driver->connect("tcp://localhost:3306", argv[1], argv[2]);

        con->setSchema("ngt");

        sql::PreparedStatement *pstmt = con->prepareStatement("INSERT INTO `index` (`objects`, `distances`, `leafNodes`, `internalNodes`)VALUES(?, ?, ?, ?)");
        
        std::string objstr = index.getObjectString();
        membuf objbuf(const_cast<char*>(objstr.data()), objstr.size());
        std::istream objblob(&objbuf);
        pstmt->setBlob(1, &objblob);

        std::string dststr = index.getDistanceString();
        membuf dstbuf(const_cast<char*>(dststr.data()), dststr.size());
        std::istream dstblob(&dstbuf);
        pstmt->setBlob(2, &dstblob);

        std::string lefstr = index.getLeafNodeString();
        membuf lefbuf(const_cast<char*>(lefstr.data()), lefstr.size());
        std::istream lefblob(&lefbuf);
        pstmt->setBlob(3, &lefblob);

        std::string itrstr = index.getInternalNodeString();
        membuf itrbuf(const_cast<char*>(itrstr.data()), itrstr.size());
        std::istream itrblob(&itrbuf);
        pstmt->setBlob(4, &itrblob);

        pstmt->execute();
    } catch (sql::SQLException e) {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }

    return 0;
}
