#!/usr/bin/env python3
"""
GitHub Actions Workflow Validator
Validates workflow files for syntax and common issues
"""
import os
import yaml
import sys
from pathlib import Path

def validate_workflow_file(filepath):
    """Validate a single workflow file"""
    print(f"Validating: {filepath}")
    
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
            workflow = yaml.safe_load(content)
        
        if workflow is None:
            print(f"  ❌ Empty or invalid YAML file")
            return False
        
        # Basic structure validation
        # Note: 'on' is parsed as boolean True by YAML, so we check for both
        required_keys = ['name', 'jobs']
        trigger_key = 'on' in workflow or True in workflow
        
        for key in required_keys:
            if key not in workflow:
                print(f"  ❌ Missing required key: {key}")
                return False
        
        if not trigger_key:
            print(f"  ❌ Missing trigger configuration ('on' key)")
            return False
        
        # Validate jobs structure
        if not isinstance(workflow['jobs'], dict):
            print(f"  ❌ 'jobs' must be a dictionary")
            return False
        
        for job_name, job_config in workflow['jobs'].items():
            if 'runs-on' not in job_config:
                print(f"  ❌ Job '{job_name}' missing 'runs-on'")
                return False
        
        print(f"  ✅ Valid workflow file")
        return True
        
    except yaml.YAMLError as e:
        print(f"  ❌ YAML syntax error: {e}")
        return False
    except Exception as e:
        print(f"  ❌ Error reading file: {e}")
        return False

def main():
    """Main validation function"""
    workflows_dir = Path('.github/workflows')
    
    if not workflows_dir.exists():
        print("❌ No .github/workflows directory found")
        return False
    
    workflow_files = list(workflows_dir.glob('*.yml')) + list(workflows_dir.glob('*.yaml'))
    
    if not workflow_files:
        print("❌ No workflow files found")
        return False
    
    print(f"Found {len(workflow_files)} workflow files")
    
    all_valid = True
    for workflow_file in workflow_files:
        if not validate_workflow_file(workflow_file):
            all_valid = False
    
    if all_valid:
        print("\n✅ All workflow files are valid!")
        return True
    else:
        print("\n❌ Some workflow files have issues")
        return False

if __name__ == "__main__":
    success = main()
    sys.exit(0 if success else 1)