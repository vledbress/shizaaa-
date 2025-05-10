#include "Application.h"

Application::~Application()
{
    glfwTerminate();
}

Application::Application(int width, int height, const std::string& path_to_exe)
    : screen(width, height, true),
    camera({ 0,0,3 }, { 0,0,-1 }, 90.f),
    resource_manager(path_to_exe),
    limiter(75)
{
    modelLoc = viewLoc = projLoc = -1;
}

bool Application::init()
{
    if (!glfwInit()) {
        std::cerr << "Ошибка инициализации GLFW!" << std::endl;
        return false; // Исправлено: возвращаем false вместо -1
    }

    if (!screen.isInited()) return false;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Ошибка инициализации GLAD!" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    resource_manager.addProgram("ilka", "shaders/color_3d/vertex3dshader.txt", "shaders/color_3d/fragment3dshader.txt")->use();
    GLuint shaderProgram = resource_manager.getProgram("ilka")->getID();

    modelLoc = glGetUniformLocation(shaderProgram, "model");
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    projLoc = glGetUniformLocation(shaderProgram, "projection");

    glfwSetWindowUserPointer(screen.getWin(), this);
    glfwSetKeyCallback(screen.getWin(), key_callback);

    event_manager.subscribe<KeyPressEvent>([this](const KeyPressEvent& e) {
        if (e.getAction() == GLFW_PRESS || e.getAction() == GLFW_REPEAT) {
            float dt = limiter.getDeltaTime();
            float speed = 10.f;
            if (e.getKey() == GLFW_KEY_S) {
                camera.move({ 0, 0, dt * speed });
            }
            else if (e.getKey() == GLFW_KEY_W) {
                camera.move({ 0, 0, -dt * speed });
            }
            else if (e.getKey() == GLFW_KEY_A) {
                camera.move({ -dt * speed, 0, 0 });
            }
            else if (e.getKey() == GLFW_KEY_D) {
                camera.move({ dt * speed, 0, 0 });
            }
        }
        });


    return true;
}







//void Application::run()
//{
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    Actor actor(std::make_shared<Mesh>());
//    actor.get_mesh()->use();
//
//
//    float angle = 0.0f;
//    float rotationspeed = 90.f; 
//
//    
//    glm::mat4 projection = glm::perspective(glm::radians(camera.get_fov()), screen.aspect(), 0.1f, 100.0f);
//    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//    actor.rotate({ 0, 45, 0 });
//
//    while (!glfwWindowShouldClose(screen.getWin())) {
//        double dt = limiter.getDeltaTime();
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        //angle += rotationspeed * dt;
//
//        actor.rotate({ rotationspeed * dt , 0, 0 });
//        //actor.rotate({ , 0, 0,  });
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(actor.get_model()));
//        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.get_view()));
//
//        glDrawElements(GL_TRIANGLES, actor.get_indices(), GL_UNSIGNED_INT, 0);
//        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//        glfwSwapBuffers(screen.getWin());
//        screen.update();
//        limiter.wait();
//    }
//}

void Application::test_run()
{
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    auto shader = resource_manager.addProgram("instance2",
        "shaders/instanced_2.0/vertex.txt",
        "shaders/instanced_2.0/fragment.txt");

    shader->use();
    std::cout << shader->compiled();
    
    GLuint shaderProgram = shader->getID();
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    projLoc = glGetUniformLocation(shaderProgram, "projection");
    

    glm::mat4 projection = glm::perspective(glm::radians(camera.get_fov()), screen.aspect(), 0.1f, 100.0f);
    

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.get_view()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    Mesh mesh;
    mesh.use();

    int count = 0;
    float spacing = 3.f;
    int side = 10; // 10 x 10 x 10 = 1000
    std::vector<Actor*> actors;
    std::vector<glm::mat4> models;

    for (int x = 0; x < side; ++x) {
        for (int y = 0; y < side; ++y) {
            for (int z = 0; z < side; ++z) {
                Actor* actor = new Actor;
                actor->move({ x * spacing - 10.f, y * spacing - 10.f, z * spacing - 10.f});
                actors.push_back(actor);
                models.push_back(actor->get_model());
                mesh.add_index(count++);
                
            }
        }
    }
    
    
    
    SSBO ssbo;
    ssbo.set_data(models);

    

    while (!glfwWindowShouldClose(screen.getWin())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElementsInstanced(GL_TRIANGLES, mesh.get_indices(), GL_UNSIGNED_INT, 0, models.size());
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.get_view()));
        glfwSwapBuffers(screen.getWin());
        screen.update();
        limiter.wait();
    }

    for (auto el : actors) {
        delete el;
    }
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    KeyPressEvent kpe(key, scancode, action, mods);
    auto events = app->get_event_manager();
    events.emit(kpe);
}
