# Contributing to ESP32 PlatformIO Project Template

Thank you for your interest in contributing! This document provides guidelines and information for contributors.

## 🚀 Quick Start

1. **Fork the repository**
2. **Clone your fork**: `git clone https://coff33ninja/YOUR_USERNAME/ESP32-PlatformIO-Project-Template.git`
3. **Set up development environment**: `.\build.ps1 setup`
4. **Create a feature branch**: `git checkout -b feature/your-feature-name`
5. **Make your changes and test thoroughly**
6. **Submit a pull request**

## 📋 Development Setup

### Prerequisites
- **PlatformIO**: Install via VS Code extension or CLI
- **Python 3.8+**: For development scripts
- **Git**: For version control
- **ESP32 Development Board**: For testing (optional)

### Environment Setup
```bash
# Install dependencies
pip install -r requirements.txt

# Run setup script
python scripts/setup.py

# Verify installation
.\build.ps1 status
```

## 🛠️ Development Workflow

### Code Style
- **C/C++**: Follow Arduino/ESP32 conventions
- **Python**: Use Black formatter (`black scripts/`)
- **Documentation**: Clear, concise comments and README updates

### Testing
```bash
# Build all environments
.\build.ps1 build-all

# Run code analysis
pio check

# Test with hardware (if available)
.\build.ps1 deploy
```

### Commit Guidelines
We use [Conventional Commits](https://www.conventionalcommits.org/):

- `feat:` New features
- `fix:` Bug fixes
- `docs:` Documentation changes
- `style:` Code style changes
- `refactor:` Code refactoring
- `test:` Test additions/changes
- `chore:` Maintenance tasks

**Examples:**
```
feat: add WiFi configuration generator
fix: resolve serial monitor connection issues
docs: update installation instructions
```

## 🎯 Contribution Areas

### High Priority
- **Hardware compatibility**: Support for different ESP32 variants
- **Library examples**: More custom library demonstrations
- **Documentation**: Tutorials, guides, troubleshooting
- **Testing**: Automated testing improvements

### Medium Priority
- **Build system**: Cross-platform improvements
- **Monitoring tools**: Enhanced debugging capabilities
- **CI/CD**: Workflow optimizations
- **Security**: Best practices and scanning

### Low Priority
- **UI improvements**: Better web interfaces
- **Performance**: Optimization opportunities
- **Integration**: Third-party service connections

## 📝 Pull Request Process

### Before Submitting
1. **Test thoroughly**: Ensure all environments build successfully
2. **Update documentation**: README, comments, examples
3. **Run quality checks**: Linting, formatting, security scans
4. **Write clear commit messages**: Follow conventional commit format

### PR Requirements
- [ ] **Descriptive title**: Clear, concise description of changes
- [ ] **Detailed description**: What, why, and how of your changes
- [ ] **Testing evidence**: Screenshots, logs, or test results
- [ ] **Documentation updates**: If applicable
- [ ] **Breaking changes**: Clearly marked and explained

### Review Process
1. **Automated checks**: CI/CD pipeline must pass
2. **Code review**: Maintainer review and feedback
3. **Testing**: Manual testing if needed
4. **Approval**: Final approval and merge

## 🐛 Bug Reports

### Before Reporting
- **Search existing issues**: Check if already reported
- **Test with latest version**: Ensure bug exists in current version
- **Minimal reproduction**: Create smallest possible example

### Bug Report Template
```markdown
**Describe the bug**
Clear description of the issue

**To Reproduce**
Steps to reproduce the behavior:
1. Go to '...'
2. Click on '....'
3. See error

**Expected behavior**
What you expected to happen

**Environment:**
- OS: [e.g. Windows 10]
- PlatformIO Version: [e.g. 6.1.0]
- ESP32 Board: [e.g. ESP32-DevKitC]
- Project Version: [e.g. 1.0.0]

**Additional context**
Any other context about the problem
```

## 💡 Feature Requests

### Before Requesting
- **Check existing requests**: Avoid duplicates
- **Consider scope**: Ensure it fits project goals
- **Think about implementation**: Consider complexity and maintenance

### Feature Request Template
```markdown
**Is your feature request related to a problem?**
Clear description of the problem

**Describe the solution you'd like**
Clear description of desired feature

**Describe alternatives you've considered**
Alternative solutions or features

**Additional context**
Any other context, screenshots, or examples
```

## 🔧 Development Guidelines

### Code Quality
- **Readability**: Clear, self-documenting code
- **Modularity**: Well-organized, reusable components
- **Error handling**: Proper error checking and recovery
- **Performance**: Efficient resource usage

### Documentation
- **Code comments**: Explain complex logic
- **README updates**: Keep documentation current
- **Examples**: Provide working examples
- **API documentation**: Document public interfaces

### Security
- **Input validation**: Sanitize all inputs
- **Credential handling**: Never commit secrets
- **Dependencies**: Keep libraries updated
- **Vulnerability scanning**: Regular security checks

## 🤝 Community Guidelines

### Be Respectful
- **Inclusive language**: Welcoming to all contributors
- **Constructive feedback**: Focus on code, not person
- **Patient help**: Support newcomers
- **Professional tone**: Maintain respectful communication

### Collaboration
- **Open communication**: Discuss major changes first
- **Knowledge sharing**: Help others learn
- **Credit attribution**: Acknowledge contributions
- **Conflict resolution**: Address disagreements constructively

## 📞 Getting Help

### Resources
- **Documentation**: Check README and wiki first
- **Issues**: Search existing issues and discussions
- **Examples**: Review example code and libraries
- **Community**: Engage with other contributors

### Contact
- **GitHub Issues**: For bugs and feature requests
- **GitHub Discussions**: For questions and ideas
- **Pull Requests**: For code contributions
- **Email**: For private/security concerns

## 🏆 Recognition

Contributors are recognized through:
- **GitHub contributors list**: Automatic recognition
- **Release notes**: Major contributions highlighted
- **Documentation**: Contributor acknowledgments
- **Community**: Public appreciation for valuable contributions

## 📄 License

By contributing, you agree that your contributions will be licensed under the same license as the project (MIT License).

---

Thank you for contributing to the ESP32 PlatformIO Project Template! Your efforts help make embedded development more accessible and enjoyable for everyone.