Machine Learning
============

Machine learning is about optimization. In learning via optimization, we define an error function (loss function) on the model and try to optimize it, i.e., try to find the optimal parameters of the model by optimization techniques borrowed from optimization literature. 

Machine learning is about algorithms. In decision/regression trees, we need to write a recursive-learning algorithm to classify the data arriving at each decision node, and we also need to write a recursive code to generate the decision tree structure.

Machine learning is about statistics. We usually assume Gaussian noise on the data, we assume multivariate normal distribution on class covariance matrices in quadratic discriminant analysis, and we use cross-validation or bootstrapping to generate multiple training sets. 

Machine learning is about models. In decision trees, the data structure is a binary/L-ary tree depending on the type of the features and the decision function used.

Machine learning is about performance metrics. In classification, we use accuracy if we want to get a crude estimate on the performance of the classifier. If we need more details on pairwise classes, confusion matrix comes in handy. If the dataset has two classes, more metrics follow: precision, recall, true positive rate, false positive rate, F-measure, etc. 

What is machine learning about? Like defining an elephant, we need the combination of all of these topics to define machine learning: we start machine learning by assuming a certain model on the data, use algorithmic and/or optimization and/or statistical techniques to learn the parameters of that model (which is sometimes defined as curve fitting), and use performance metrics to evaluate our model/algorithm/classifier.

# Algorithms

## Nearest Neighbor

The most commonly used representative of nonparametric algorithms is the nearest neighbor. The assumption of nearest neighbor is simple, the world does not change much, i.e., similar things perform similarly. Therefore, we only need to store the dataset itself and make the decision on the test instance based on the similarity of it to the instances in the dataset. In other words, the class label of an instance is strongly influenced by its nearby instances.

## Parametric Classification

If the class distributions are assumed to follow Gaussian density, we obtain our first parametric classifier, namely, quadratic discriminant. The number of parameters, i.e., the model complexity is Kd + Kd (d + 1) / 2, the first part is for class means and the second part for class covariance matrices.

We can assume a single shared covariance matrix for all classes. In this case, simplifying the function reduces to our second classifier, namely, linear discriminant. The model complexity is Kd + d (d + 1) / 2, where the first part is for class means and the second part for shared covariance matrix.

When we assume all off-diagonals of the shared covariance matrix are zero; we get the naive Bayes classifier. The model complexity is Kd + d, where the first part is for class means and the second part for the diagonal of the shared covariance matrix.

We further reduce by taking priors equal and a single covariance value s. In this case, we get the nearest mean classifier and the model complexity is only Kd + 1.

## Decision Trees

Decision trees have a tree-based structure where each non-leaf node m implements a decision function, f<sub>m</sub>(x), and each leaf node corresponds to a class decision. Second, they are one of most interpretable learning algorithms available. When written as a set of IF-THEN rules, the decision tree can be transformed into a human-readable format, which then can be modified and/or validated by human experts in their corresponding domains.

## Kernel Machines

Kernel machines, in other words, support vector machines, are maximum margin methods, where the model is written as a weighted sum of support vectors. Kernel machines are discriminative methods, i.e., they are only interested in the instances across the class boundaries in classification, or instances across the regressor in regression. For obtaining the optimal separating hyperplane, kernel machines try to maximize separability, or margin, and write the problem as a quadratic optimization problem, whose solution gives us support vectors.

## Neural Networks

Artificial neural networks (ANN) take their inspiration from the brain. The brain consists of billions of neurons and these neurons are interconnected and work in parallel, which makes the brain a powerful computing machine. Each neuron is connected through synapses to thousands of neurons and the firing of a neuron depends on those synapses.

There are three types of neurons (units) in ANN. Each unit except the input unit takes an input and calculates an output. Input units represent a single input feature x<sub>i</sub> or the bias = +1. Hidden units calculate an intermediate output from its inputs. They first combine their inputs linearly and then use nonlinear activation functions to map that linear combination to a nonlinear space. Output units calculate the output of the ANN.

Video Lectures
============

[<img src="https://github.com/StarlangSoftware/Classification/blob/master/video1.jpg" width="50%">](https://youtu.be/1p0zBhji0YE)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video2.jpg width="50%">](https://youtu.be/xvNGStxTEsU)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video3.jpg width="50%">](https://youtu.be/EfDoMKHl_iY)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video4.jpg width="50%">](https://youtu.be/4Y-1r0H8vZc)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video5.jpg width="50%">](https://youtu.be/1b5sEp321Lo)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video6.jpg width="50%">](https://youtu.be/_bM4RmKMo3I)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video7.jpg width="50%">](https://youtu.be/xGHskyTb35s)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video8.jpg width="50%">](https://youtu.be/ZdFUDFmOjL4)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video9.jpg width="50%">](https://youtu.be/O0W99NhiFug)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video10.jpg width="50%">](https://youtu.be/k-sTBA9HGVc)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video11.jpg width="50%">](https://youtu.be/yDlcLtVJDGk)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video12.jpg width="50%">](https://youtu.be/7qxxNzymzLI)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video13.jpg width="50%">](https://youtu.be/sVzu7UYOFXM)[<img src=https://github.com/StarlangSoftware/Classification/blob/master/video14.jpg width="50%">](https://youtu.be/OynNcw2IItg)

For Developers
============
You can also see [Python](https://github.com/starlangsoftware/Classification-Py), [Cython](https://github.com/starlangsoftware/Classification-Cy), [Java](https://github.com/starlangsoftware/Classification), 
[C++](https://github.com/starlangsoftware/Classification-CPP), [Swift](https://github.com/starlangsoftware/Classification-Swift), 
[Js](https://github.com/starlangsoftware/Classification-Js), or [C#](https://github.com/starlangsoftware/Classification-CS) repository.

## Requirements

* [C++ Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C++ Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called Classification-CPP will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/Classification-CPP.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu. After compilation process, user can run TestClassification.cpp.

Detailed Description
============

+ [Classification Algorithms](#classification-algorithms)
+ [Statistical Tests](#statistical-tests)

## Classification Algorithms

Algoritmaları eğitmek için

	Classifier_ptr train(Instance_list_ptr train_set, const void *parameter)

Eğitilen modeli bir veri örneği üstünde sınamak için

	char* (*predict)(const void* model, const Instance* instance)

Karar ağacı algoritması C45 sınıfında

Bagging algoritması Bagging sınıfında

Derin öğrenme algoritması DeepNetwork sınıfında

KMeans algoritması KMeans sınıfında

Doğrusal ve doğrusal olmayan çok katmanlı perceptron LinearPerceptron ve 
MultiLayerPerceptron sınıflarında

Naive Bayes algoritması NaiveBayes sınıfında

K en yakın komşu algoritması Knn sınıfında

Doğrusal kesme analizi algoritması Lda sınıfında

İkinci derece kesme analizi algoritması Qda sınıfında

Destek vektör makineleri algoritması Svm sınıfında

RandomForest ağaç tabanlı ensemble algoritması RandomForest sınıfında

Basit dummy ve rasgele sınıflandırıcı gibi temel iki sınıflandırıcı Dummy ve 
RandomClassifier sınıflarında

## Statistical Tests

İstatistiksel testler için Combined5x2F, Combined5x2t, Paired5x2t, Pairedt, Sign sınıfları

For Contibutors
============

### Conan Setup

1. First install conan.

pip install conan

Instructions are given in the following page:

https://docs.conan.io/2/installation.html

2. Add conan remote 'ozyegin' with IP: 104.247.163.162 with the following command:

conan remote add ozyegin http://104.247.163.162:8081/artifactory/api/conan/conan-local --insert

3. Use the comman conan list to check for installed packages. Probably there are no installed packages.

conan list

### conanfile.py file

1. Put the correct dependencies in the requires part
```
    requires = ["math_c/1.0.0", "data_structure_c/1.0.0", "classification_c/1.0.0"]
```

2. Default settings are:
```
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": True, "fPIC": True}
    exports_sources = "src/*", "Test/*"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(conanfile=self, keep_path=False, src=join(self.source_folder), dst=join(self.package_folder, "include"), pattern="*.h")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.a")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.so")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.dylib")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "bin"), pattern="*.dll")

    def package_info(self):
        self.cpp_info.libs = ["ComputationalGraph"]
```

### CMakeLists.txt file
1. Set the C standard with compiler flags.
```
	set(CMAKE_C_STANDARD 17)
	set(CMAKE_C_FLAGS "-O3")
```
2. Dependent packages should be given with find_package.
```
	find_package(util_c REQUIRED)
	find_package(data_structure_c REQUIRED)
```
3. For library part, use add_library and target_link_libraries commands. Use m library for math linker in Linux.
```
	add_library(Math src/Distribution.c src/Distribution.h src/DiscreteDistribution.c src/DiscreteDistribution.h src/Vector.c src/Vector.h src/Eigenvector.c src/Eigenvector.h src/Matrix.c src/Matrix.h src/Tensor.c src/Tensor.h)
	target_link_libraries(Math util_c::util_c data_structure_c::data_structure_c m)
```
4. For executable tests, use add_executable and target_link_libraries commands. Use m library for math linker in Linux.
```
	add_executable(DiscreteDistributionTest src/Distribution.c src/Distribution.h src/DiscreteDistribution.c src/DiscreteDistribution.h src/Vector.c src/Vector.h src/Eigenvector.c src/Eigenvector.h src/Matrix.c src/Matrix.h src/Tensor.c src/Tensor.h Test/DiscreteDistributionTest.c)
	target_link_libraries(DiscreteDistributionTest util_c::util_c data_structure_c::data_structure_c m)
```

### Data files
1. Add data files to the cmake-build-debug folder.

### C files
1. Define structs as class counterparts.
```
	typedef struct {
	    double *data;       // Flattened data array
 	   	int *shape;         // Shape of the tensor
	    int *strides;       // Strides for each dimension
 	   	int dimensions;     // Number of dimensions
  	  	int total_elements;
	} Tensor;
```
2. Define also typedefs for pointer to those structs.
```
	typedef Tensor *Tensor_ptr;
```
3. Put all those definitions to the header files with prototypes of functions.
4. Constructor method(s) should allocate a pointer of struct and fill the details and return the pointer.
```
Vector_ptr create_vector(Array_list_ptr values) {
    Vector_ptr result = malloc_(sizeof(Vector));
    result->values = values;
    result->size = values->size;
    return result;
}
```
5. Destructor method should be defined for each struct and deallocate the object and its contents if allocated.
```
void free_vector(Vector_ptr vector) {
    free_array_list(vector->values, free_);
    free_(vector);
}
```
6. If there is multiple inheritance, then define the super class inside the subclass, which also should be defined inside its own subclass etc.
```
struct sgd_momentum {
    Optimizer optimizer;
    Hash_map_ptr velocity_map;
    double momentum;
};
struct Adam {
    Sgd_momentum sgd;
    Hash_map_ptr momentum_map;
    double beta2;
    double epsilon;
    double current_beta1;
    double current_beta2;
};
struct AdamW {
    Adam adam;
    double weight_decay;
};
```
7. If there is overloading, and subclasses should override the method, you can add pointers to the functions and set them in the constructor.
```
struct function {
    Function_type function_type;
    Tensor_ptr (*calculate)(const void*, const Tensor*);
    Tensor_ptr (*derivative)(const void*, const Tensor*, const Tensor*);
};
Elu_ptr create_elu(const double a) {
    Elu_ptr delu = malloc_(sizeof(Elu));
    delu->a = a;
    delu->function.function_type = ELU;
    delu->function.calculate = calculate_elu;
    delu->function.derivative = derivative_elu;
    return delu;
}
```
8. Instanceof could be done using an enumerated type defined in the parent class.
```
enum optimizer_type {
    OPTIMIZER, ADAM, ADAM_W, SGD_MOMENTUM, SGD,
};
typedef enum optimizer_type Optimizer_type;
struct optimizer {
    Optimizer_type type;
```
9. If needed, hash function should be declared for the struct.
```
	unsigned int hash_function_computational_node(const Computational_node *node, int N) {
    	return ((uintptr_t)node) % N;
	}
```
10. If needed, comparator function should be declared for the struct.
```
int compare_annotated_word(const Annotated_word *word1, const Annotated_word *word2) {
    return compare_string(word1->name, word2->name);
}
```
11. Data Structures: For hashmap, linked hash map and hashset, use create_hash_map, create_linked_hash_map, and create_hash_set in data structure library. There are default string and integer versions of hash_map.
```
Hash_map_ptr create_hash_map(unsigned int (*hash_function)(const void *, int), int (*key_compare)(const void *, const void *));
Linked_hash_map_ptr create_linked_hash_map(unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *));
Hash_map_ptr create_string_hash_map();
Hash_map_ptr create_integer_hash_map();
Hash_set_ptr create_hash_set(unsigned int (*hash_function)(const void *, int), int (*compare)(const void *, const void *));
```
12. Data Structures: For array list, use create_array_list in data structure library..
```
Array_list_ptr create_array_list();
```
13. Data Structures: For linked list, use linked_list in data structure library..
```
Linked_list_ptr create_linked_list(int (*compare)(const void *, const void *));
```
14. Data Structures: For queue and stack, use queue and stack in data structure library.
```
Queue_ptr create_queue();
Stack_ptr create_stack();
```
15. Data Structures: For hash map that is counting items, use counter hash map in data structure library.
```
Counter_hash_map_ptr
create_counter_hash_map(unsigned int (*hash_function)(const void *, int), int (*key_compare)(const void *, const void *));
```
16. Do not forget to comment each function.
```
	/**
 	* Initializes a tensor with given data and shape. Data is cloned in the tensor
	*
 	* @param data Flattened array representing the tensor data.
 	* @param shape Array representing the shape of the tensor.
 	* @param dimensions Size of the shape array.
 	* @return Pointer to the created tensor. Returns NULL on failure.
 	*/
	Tensor_ptr create_tensor(const double *data, const int *shape, int dimensions) {
```
17. Function names should follow snake case case.
```
	Tensor_ptr tensor_get(const Tensor *tensor, const int *dimensions, int size) {
```
18. All heap allocations should be done with malloc_, calloc_, realloc_ taken from the memory management library.
```
    int *new_shape = malloc_((tensor->dimensions - size) * sizeof(int));
```
19. All heap deallocations should be done with free_ taken from the memory management library.
```
    free_(new_shape);
```
20. DO NOT write getter and setter methods.
21. If there are multiple constructors for a class, define them as constructor1, constructor2, ....
```
Tensor_ptr create_tensor(const double *data, const int *shape, int dimensions);

Tensor_ptr create_tensor2(const int *shape, int dimensions);

Tensor_ptr create_tensor3(double *data, const int *shape, int dimensions);

Tensor_ptr create_tensor4(const int *shape, int dimensions);
```
22. Use separate main method for testing purposes.
```
int main() {
    start_medium_memory_check();
    testColumnWiseNormalize();
    testMultiplyWithConstant();
    testDivideByConstant();
    end_memory_check();
}
```
23. Testing main method should start with memory check and end with memory check.
```
int main() {
    start_medium_memory_check();
    testColumnWiseNormalize();
    testMultiplyWithConstant();
    testDivideByConstant();
    end_memory_check();
}
```
24. Enumerated types should be declared with enum.
```
enum category_type{
    MATHEMATICS, SPORT, MUSIC, SLANG, BOTANIC,
    PLURAL, MARINE, HISTORY, THEOLOGY, ZOOLOGY,
    METAPHOR, PSYCHOLOGY, ASTRONOMY, GEOGRAPHY, GRAMMAR,
    MILITARY, PHYSICS, PHILOSOPHY, MEDICAL, THEATER,
    ECONOMY, LAW, ANATOMY, GEOMETRY, BUSINESS,
    PEDAGOGY, TECHNOLOGY, LOGIC, LITERATURE, CINEMA,
    TELEVISION, ARCHITECTURE, TECHNICAL, SOCIOLOGY, BIOLOGY,
    CHEMISTRY, GEOLOGY, INFORMATICS, PHYSIOLOGY, METEOROLOGY,
    MINERALOGY
};
```
25. Every header file should start with
```
#ifndef MATH_DISTRIBUTION_H
#define MATH_DISTRIBUTION_H
```
and end with
```
#endif //MATH_DISTRIBUTION_H
```
26. Use regular package for regular expression handling.
```
	void check_match(char* expression, char* word){
    	Regular_expression_ptr re = create_regular_expression(expression);
    	if (!full_matches(re, word)){
        	printf("Mismatch %s %s\n", re->expression, word);
    	}
    	free_regular_expression(re);
	}
```
27. Do not forget to use const expression for parameters, if they will not be changed in the function.
```
bool frame_lexical_unit_exists(const Frame* frame, const char *synSetId);
```
28. For dynamic string handling, use util package with stringutils.
```
struct string {
    char *s;
    int max_size;
};
typedef struct string String;
typedef String *String_ptr;
String_ptr create_string();
String_ptr create_string2(const char *s);
String_ptr create_string3(const char* s1, const char* s2);
String_ptr create_string4(const char* s1, const char* s2, const char* s3);
```
29. Foor boolean type, use bool.
```
bool check_definition(const Data_set* data_set, const Instance* instance);
```
30. Use xmlparser package for parsing xml files.
```
    Xml_document_ptr doc = create_xml_document("test.xml");
